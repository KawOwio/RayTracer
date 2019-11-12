#include "Tracer.h"

glm::ivec3 Tracer::traceRay(Ray _myRay)
{
	Sphere mySphere;
	intersectionReturn myResult;

	for (int o = 0; o < objects.size(); o++)
	{
		myResult = mySphere.intersection(_myRay);

		if (myResult.intersection == true)
		{
			glm::ivec3 colour = mySphere.shadePixel(_myRay, myResult.intersectionPoint);
			return colour;
		}
		else
		{
			return glm::ivec3(0, 0, 0);
		}
	}
}

	