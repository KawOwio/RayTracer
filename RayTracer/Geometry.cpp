#include "Geometry.h"

intersectionReturn Geometry::intersection(Ray _myRay, Sphere _mySphere)
{
	float d;
	float dotProduct;
	
	glm::vec3 rayOrigin = _myRay.origin;
	glm::vec3 rayDirection = _myRay.direction;
	glm::vec3 worldOrigin = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 a = rayOrigin;
	glm::vec3 P = _mySphere.getCentre();
	glm::vec3 Pa = P - a;
	glm::vec3 n = rayDirection;

	float radius = _mySphere.getRadius();

	dotProduct = (glm::dot(Pa, n));
	d = glm::length(Pa - (dotProduct * n));
	
	//check if ray is inside of the sphere
	if (glm::length(P - a) <= radius || dotProduct <= 0)
	{
		check.distance = 9999999.9f;
		_mySphere.distanceFromCamera = check.distance;
		check.intersection = false;
		return check;
	}
	else
	{
		if (radius > d)
		{
			float x = glm::sqrt(glm::pow(radius, 2) - glm::pow(d, 2));
			check.distance = dotProduct - x;
			_mySphere.distanceFromCamera = check.distance;
			check.intersection = true;
			check.intersectionPoint = (a + (dotProduct - x) * n);
		}
		else
		{
			check.distance = 99999999.9f;
			_mySphere.distanceFromCamera = check.distance;
			check.intersection = false;
		}

		return check;
	}

}

glm::vec3 Geometry::sphereNormal(glm::vec3 _centre, glm::vec3 _samplePoint)
{
	glm::vec3 directionVector;

	directionVector = glm::normalize(_samplePoint - _centre);

	return directionVector;
}