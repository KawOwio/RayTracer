#include "Tracer.h"

glm::vec3 Tracer::traceRay(Ray _myRay)
{
	intersectionReturn myResult;
	intersectionReturn myIntersection;
	Geometry geometry;

	int objectId = -1;
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

	//Check if objectId is in range from 0 to the amoubnt of spheres (3 in submited variant)
	bool inRange = objectId <= objects.size();

	if (inRange)
	{
		glm::vec3 colour = objects[objectId].shadePixel(_myRay, myIntersection.intersectionPoint);
		return colour;
	}
	
	//Background colour
	return glm::vec3(0.0f, 0.0f, 0.0f);
}