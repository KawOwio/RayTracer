#include <cmath>

#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"
#include "Sphere.h"


int main( int argc, char *argv[] )
{
	// Variable for storing window dimensions
	glm::ivec2 windowSize( 640, 480 );

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground( glm::ivec3(0,0,0) );

	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = windowSize / 2;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 255
	glm::ivec3 pixelColour( 255, 0, 0 );


	// Variable to keep track of time
	//float timer = 0.0f;

	//Creating objects
	Camera myCamera;
	Tracer myTracer;
	Ray myRay;
	Sphere mySphere;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		//MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		for (int y = 0; y < windowSize.y; y++)
		{
			pixelPosition.y = y;
			for (int x = 0; x < windowSize.x; x++)
			{
				pixelPosition.x = x;

				myRay = myCamera.generateRay(pixelPosition);
				mySphere.intersection(myRay, glm::vec3(0.0f, 0.0f, -1.0f));
				bool inter = mySphere.getIntersection();

				if (inter = true)
				{
					pixelColour = myTracer.traceRay(myRay);
				}
				else
				{
					pixelColour = glm::ivec3(0, 0, 0);
				}

				// Draw the pixel to the screen
				MCG::DrawPixel(pixelPosition, pixelColour);
				MCG::ProcessFrame();
			}
		}

		// Change our pixel's X coordinate according to time
		//pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		//timer += 1.0f / 60.0f;
	}

	return 0;
}
