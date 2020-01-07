//**********************************************************//
// 						   Ray Tracer	 					//
//			Created by Nikita Gribuska (s5065617)			//
//	   GitHub link: https://github.com/KawOwio/RayTracer	//
//**********************************************************//

#include <cmath>
#include <iostream>
#include <time.h>
#include <thread>
#include <mutex>

#include "Scene.h"

std::mutex mtx;		//mutex;
//int threads = 2;	//number of threads

void rayTrace(int _split, Scene _myScene, int _threads)
{
	glm::vec2 pixelPosition;
	glm::vec3 pixelColour;		//defuse + specular colour;
	glm::vec3 reflectedColour;	//colour gotten from a reflection

	glm::vec2 windowSize = _myScene.getWindowSize();

	int numOfObjects = _myScene.myTracer.objects.size();	//number of spheres in an array

	//Go throught every pixel; formula is for spliting the screen according to amount of threads to enable multithreading
	for (int y = (windowSize.y / _threads * (_split - 1)); y < windowSize.y / _threads * _split; y++)
	{
		pixelPosition.y = y;
		
		for (int x = 0; x < windowSize.x; x++)
		{
			pixelPosition.x = x;

			_myScene.myRay = _myScene.myCamera.generateRay(pixelPosition, windowSize);

			//temporary values
			_myScene.tempResult.distance = 9999999.9f;
			int closestId = -1;

			//find closest object to ensure that reflections aren't outputed in obstracrted objects
			for (int c = 0; c < numOfObjects; c++)
			{
				_myScene.intersectionResult = _myScene.geometry.intersection(_myScene.myRay, _myScene.myTracer.objects[c]);
				
				if (_myScene.intersectionResult.intersection == true)
				{
					if (_myScene.intersectionResult.distance < _myScene.tempResult.distance)
					{
						_myScene.tempResult = _myScene.intersectionResult;
						closestId = c;
					}
				}
			}

			bool done = false;
			bool inRange = closestId <= _myScene.myTracer.objects.size();

			if (inRange)
			{
				if (_myScene.myTracer.objects[closestId].getReflectivity() > 0 && _myScene.tempResult.intersection == true)
				{
					glm::vec3 surfaceNormal = _myScene.geometry.sphereNormal(_myScene.myTracer.objects[closestId].getCentre(), _myScene.intersectionResult.intersectionPoint);
					_myScene.myReflectionRay.direction = glm::reflect(_myScene.myRay.direction, surfaceNormal);
					_myScene.myReflectionRay.origin = _myScene.intersectionResult.intersectionPoint;

					//Check if there is an intersection between reflection ray and all other object in the array of spheres
					for (int n = 0; n < numOfObjects; n++)
					{
						_myScene.intersectionResult = _myScene.geometry.intersection(_myScene.myReflectionRay, _myScene.myTracer.objects[n]);

						if (_myScene.intersectionResult.intersection == true)
						{
							reflectedColour = _myScene.myTracer.traceRay(_myScene.myReflectionRay) * _myScene.myTracer.objects[closestId].getReflectivity();
							done = true;
						}
					}

					if (!done)
					{
						reflectedColour = glm::vec3(0.0f, 0.0f, 0.f);
						done = true;
					}

				}
				else
				{
					if (!done)
					{
						reflectedColour = glm::vec3(0.0f, 0.0f, 0.0f);
					}

				}
			}
			
			pixelColour = _myScene.myTracer.traceRay(_myScene.myRay);
			pixelColour = glm::min((pixelColour + reflectedColour), 1.0f);

			// Draw the pixel to the screen		
			mtx.lock();
			MCG::DrawPixel(pixelPosition, pixelColour * 255.0f);
			mtx.unlock();
		}
	}
	mtx.lock();
	MCG::ProcessFrame();
	mtx.unlock();
}

int main( int argc, char *argv[] )
{
	//initialising the scene
	Scene myScene;
	myScene.initialise(glm::vec2(640, 480));

	int threads = 1;
	bool entered = false;

	//Very simple menu
	while (!entered)
	{
		system("cls");
		std::cout << "Enter number of threads you want to use: ";
		std::cin >> threads;

		//Check for input to be int
		if (std::cin.fail())
		{
			entered = false;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else
		{
			entered = true;
		}
	}
	
	//Initialising and creating a window
	if( !MCG::Init( myScene.getWindowSize() ) )
	{
		// We must check if something went wrong
		return -1;
	}

	bool finished = false;
	
	//Game loop
	while (finished == false)
	{
		std::vector<std::thread *> t;	//Vector of threads

		int start_s = clock(); //gets time when rendering has started

		//Function that splits screen by number of threads
		//Each thread fills in its' own area
		for (int split = 1; split <= threads; split++)
		{
			//create threads
			t.push_back(new std::thread(rayTrace, split, myScene, threads));
		}
		for (int i = 0; i < t.size(); i++)
		{
			//wait until all threads finish
			t[i]->join();
		}

		int stop_s = clock(); //get time when rendering has finished

		std::cout << " #Threads: " << threads << "\tTime taken: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) << " seconds\n";

		finished = true;
		t.resize(0);
	}

	/*	//Game Loop for testing and gathering data
	int tempThreads = 0;
	int run = 0;
	//Game loop
	while( finished == false )
	{
		tempThreads += 1;
		//tempThreads = pow(2, run);

		std::vector<std::thread *> t;	//Vector of threads

		int start_s = clock(); //gets time when rendering has started

		//Function that splits screen by number of threads
		//Each thread fills in its' own area
		for (int split = 1; split <= tempThreads; split++)
		{
			//create threads
			t.push_back(new std::thread(rayTrace, split, myScene, tempThreads));
		}
		for (int i = 0; i < t.size(); i++)
		{
			//wait until all threads finish
			t[i]->join();
		}

		int stop_s = clock(); //get time when rendering has finished

		//std::cout << " #Threads: " << tempThreads << "\tTime taken: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) << " seconds\n";
		std::cout << (stop_s - start_s) / double(CLOCKS_PER_SEC) << "\n";

		//if (tempThreads >= myScene.getWindowSize().y)
		if (tempThreads == 64)
		{
			finished = true;
		}
		t.resize(0);
		run++;
	}
	*/

	MCG::ShowAndHold();
	//system("pause");
	return 0;
}