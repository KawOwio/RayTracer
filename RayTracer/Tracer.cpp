#include "Tracer.h"

glm::vec3 Tracer::traceRay(Ray _myRay)
{
	intersectionReturn myResult;
	intersectionReturn myIntersection;
	Geometry geometry;

	int objectId = 999999999;
	myIntersection.distance = 999999.9f;

	for (int o = 0; o < objects.size(); o++)
	{
		myResult = geometry.intersection(_myRay, objects[o]);

		if (myResult.intersection == true)
		{
			if (myResult.distance < myIntersection.distance)
			{
				myIntersection = myResult;
				objectId = o;
			}
		}
	}

	if (objectId == 0 || objectId == 1)
	{
		glm::vec3 colour = objects[objectId].shadePixel(_myRay, myIntersection.intersectionPoint);
		return colour;
	}
	
	//Background colour
	return glm::vec3(0.01f, 0.01f, 0.1f);
}