#include "Tracer.h"

glm::vec3 Tracer::traceRay(Ray _myRay)
{
	intersectionReturn myResult;
	Geometry geometry;

	for (int o = 0; o < objects.size(); o++)
	{
		myResult = geometry.intersection(_myRay, objects[o]);

		if (myResult.intersection == true)
		{
			glm::vec3 colour = objects[o].shadePixel(_myRay, myResult.intersectionPoint);
			return colour;
		}
		
	}
	//Background colour
	return glm::vec3(0.01f, 0.01f, 0.1f);
}