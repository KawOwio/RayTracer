#include <cmath>
#include <iostream>
#include <time.h>
#include <thread>
#include <mutex>

#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"
#include "Sphere.h"

glm::ivec2 windowSize(640, 480);
std::mutex mtx;
int threads = 1;

void t1(int _split)
{
	glm::ivec2 pixelPosition;
	glm::vec3 pixelColour;

	Camera myCamera(glm::mat4(1), glm::perspective(0.7f, ((float)windowSize.x / (float)windowSize.y), 0.1f, 100.0f));
	Tracer myTracer;
	Ray myRay;
	Sphere mySphere(glm::vec3(0.0f, 0.0f, -100.0f), 25.0f);

	myTracer.objects.push_back(mySphere);

	for (int y = (windowSize.y / threads * (_split - 1)); y < windowSize.y / threads * _split; y++)
	{
		pixelPosition.y = y;

		for (int x = 0; x < windowSize.x; x++)
		{
			pixelPosition.x = x;

			myRay = myCamera.generateRay(pixelPosition, windowSize);
			pixelColour = myTracer.traceRay(myRay);

			// Draw the pixel to the screen		
			mtx.lock();
			MCG::DrawPixel(pixelPosition, pixelColour * 255.0f);
			mtx.unlock();
		}
		mtx.lock();
		MCG::ProcessFrame();
		mtx.unlock();
	}
}

int main( int argc, char *argv[] )
{
	//Initialising and creating a window
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		return -1;
	}

	// Sets every pixel to the same colour
	MCG::SetBackground( glm::ivec3(0,0,0) );

	//glm::ivec2 pixelPosition;
	//glm::vec3 pixelColour;

	//Creating objects



	bool finished = false;

	//Game loop
	while( finished == false )
	{
		int start_s = clock(); //gets time when rendering has started
		std::vector<std::thread *> t;
		for (int split = 1; split <= threads; split++)
		{
			//create threads
			t.push_back(new std::thread(t1, split));
		}
		for (int i = 0; i < t.size(); i++)
		{
			//wait until all threads finish
			t[i]->join();
		}

		int stop_s = clock(); //get time when rendering has finished
		std::cout << "Time taken: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) << " seconds\n";
		finished = true;
		t.resize(0);
	}

	system("pause");
	return 0;
}