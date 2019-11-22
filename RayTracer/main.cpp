#include <cmath>
#include <iostream>
#include <time.h>
#include <thread>
#include <mutex>

#include "Scene.h"

std::mutex mtx;
int threads = 4;	//2.3 sec

void t1(int _split, Scene _myScene)
{
	glm::ivec2 pixelPosition;
	glm::vec3 pixelColour;

	glm::ivec2 windowSize = _myScene.getWindowSize();

	for (int y = (windowSize.y / threads * (_split - 1)); y < windowSize.y / threads * _split; y++)
	{
		pixelPosition.y = y;

		for (int x = 0; x < windowSize.x; x++)
		{
			pixelPosition.x = x;

			_myScene.myRay = _myScene.myCamera.generateRay(pixelPosition, windowSize);
			_myScene.intersectionResult = _myScene.geometry.intersection(_myScene.myRay, _myScene.myTracer.objects[0]);

			pixelColour = _myScene.myTracer.traceRay(_myScene.myRay);

			//if (_myScene.myTracer.objects[0].getReflectivity() > 0)
			//{
			//	//_myScene.myRay = _myScene.myCamera.generateRay(_myScene.intersectionResult.intersectionPoint, windowSize);
			//	_myScene.myRay.origin = _myScene.intersectionResult.intersectionPoint;
			//	_myScene.myRay.direction = glm::reflect(_myScene.intersectionResult.intersectionPoint, _myScene.geometry.sphereNormal(_myScene.myTracer.objects[0].getCentre(), _myScene.intersectionResult.intersectionPoint));
			//	pixelColour = _myScene.myTracer.traceRay(_myScene.myRay);
			//}
			//else
			//{
			//	pixelColour = _myScene.myTracer.traceRay(_myScene.myRay);
			//}
			
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
	Scene myScene;
	myScene.initialise(glm::ivec2(640, 480));

	//Initialising and creating a window
	if( !MCG::Init( myScene.getWindowSize() ) )
	{
		// We must check if something went wrong
		return -1;
	}

	// Sets every pixel to the same colour
	MCG::SetBackground( glm::ivec3(0,0,0) );

	bool finished = false;

	//Game loop
	while( finished == false )
	{
		int start_s = clock(); //gets time when rendering has started
		std::vector<std::thread *> t;
		for (int split = 1; split <= threads; split++)
		{
			//create threads
			t.push_back(new std::thread(t1, split, myScene));
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