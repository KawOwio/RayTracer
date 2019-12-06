#include <cmath>
#include <iostream>
#include <time.h>
#include <thread>
#include <mutex>

#include "Scene.h"

std::mutex mtx;
int threads = 8;	//2.3 sec

void t1(int _split, Scene _myScene)
{
	glm::ivec2 pixelPosition;
	glm::vec3 pixelColour;
	glm::vec3 reflectedColour;

	glm::ivec2 windowSize = _myScene.getWindowSize();

	for (int y = (windowSize.y / threads * (_split - 1)); y < windowSize.y / threads * _split; y++)
	{
		pixelPosition.y = y;

		for (int x = 0; x < windowSize.x; x++)
		{
			pixelPosition.x = x;

			_myScene.myRay = _myScene.myCamera.generateRay(pixelPosition, windowSize);

			
			_myScene.intersectionResult = _myScene.geometry.intersection(_myScene.myRay, _myScene.myTracer.objects[0]);
			if (_myScene.mySphere.getReflectivity() > 0 && _myScene.intersectionResult.intersection == true)
			{
				glm::vec3 surfaceNormal = _myScene.geometry.sphereNormal(_myScene.mySphere.getCentre(), _myScene.intersectionResult.intersectionPoint);
				_myScene.myReflectionRay.direction = glm::reflect(_myScene.intersectionResult.intersectionPoint, surfaceNormal);
				_myScene.myReflectionRay.origin = surfaceNormal + (_myScene.myReflectionRay.direction * (float)DBL_EPSILON);

				_myScene.intersectionResult = _myScene.geometry.intersection(_myScene.myReflectionRay, _myScene.myTracer.objects[1]);

				if (_myScene.intersectionResult.intersection == true)
				{
					reflectedColour = _myScene.myTracer.traceRay(_myScene.myReflectionRay);
				}
				else
				{
					reflectedColour = glm::vec3(0.01f, 0.01f, 0.1f);
				}
				
			}
			else
			{
				reflectedColour = glm::vec3(0.0f, 0.0f, 0.0f);
			}
			

			pixelColour = _myScene.myTracer.traceRay(_myScene.myRay);

			pixelColour = glm::min((pixelColour + reflectedColour), 1.0f);
			
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
	//MCG::SetBackground( glm::ivec3(0,0,0) );

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