#include <cmath>
#include <iostream>

#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"
#include "Sphere.h"


int main( int argc, char *argv[] )
{
	glm::ivec2 windowSize(640, 480);

	//Initialising and creating a window
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		return -1;
	}

	// Sets every pixel to the same colour
	MCG::SetBackground( glm::ivec3(0,0,0) );

	glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;

	//Creating objects
	Camera myCamera(glm::mat4(1), glm::perspective(0.7f, ((float)windowSize.x / (float)windowSize.y), 0.1f, 100.0f));
	Tracer myTracer;
	Ray myRay;
	Sphere mySphere(glm::vec3(0.0f, 0.0f, -200.0f), 27.5f);
	//Sphere mySphere2(glm::vec3(10.0f, 15.0f, -200.0f), 35.5f);

	myTracer.objects.push_back(mySphere);
	//myTracer.objects.push_back(mySphere2);

	bool finished = false;

	//Game loop
	while( finished == false )
	{
		//Going through every pixel on the screen
		for (int y = 0; y < windowSize.y; y++)
		{
			pixelPosition.y = y;

			for (int x = 0; x < windowSize.x; x++)
			{
				pixelPosition.x = x;

				myRay = myCamera.generateRay(pixelPosition, windowSize);
				pixelColour = myTracer.traceRay(myRay);

				// Draw the pixel to the screen		
				MCG::DrawPixel(pixelPosition, pixelColour);

			}
			MCG::ProcessFrame();
		}

		//std::cout << "frame finished" << std::endl;
		finished = true;
	}
	
	system("pause");
	return 0;
}