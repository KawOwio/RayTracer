#include "Tracer.h"

glm::ivec3 Tracer::traceRay(Ray _myRay)
{
	intersectionReturn myResult;
	Geometry geometry;

	for (int o = 0; o < objects.size(); o++)
	{
		myResult = geometry.intersection(_myRay, objects[o]);

		if (myResult.intersection == true)
		{
			glm::ivec3 colour = objects[0].shadePixel(_myRay, myResult.intersectionPoint);
			return colour;
			//return glm::ivec3(255, 0, 0);
		}
		else
		{
			//Background colour
			return glm::ivec3(0, 0, 0);
		}
	}
}