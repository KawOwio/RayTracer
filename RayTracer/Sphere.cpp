#include "Sphere.h"

glm::ivec3 Sphere::shadePixel(Ray _myRay, glm::vec3 _intersectionPoint)
{
	return glm::ivec3(255, 0, 0);
}

intersectionReturn Sphere::intersection(Ray _myRay)
{
	float d;
	float temp;
	
	glm::vec3 rayOrigin = _myRay.origin;
	glm::vec3 rayDirection = _myRay.direction;
	glm::vec3 worldOrigin = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 a = rayOrigin;
	glm::vec3 P = centre;
	glm::vec3 Pa = P - a;
	glm::vec3 n = rayDirection;
	glm::vec3 X;

	temp = (glm::dot(Pa, n));
	d = glm::length(Pa - (temp * n));
	
	if (glm::length(P - a) <= radius || temp <= 0)
	{
		check.distance = 0.0f;
		check.intersection = false;
		return check;
	}
	else
	{
		if (radius > d)
		{
			float x = glm::sqrt(glm::pow(radius, 2) - glm::pow(d, 2));
			check.distance = temp - x;
			check.intersection = true;
			check.intersectionPoint = (a + (temp - X) * n);
		}
		else
		{
			check.distance = 0.0f;
			check.intersection = false;
		}

		return check;
	}
}

bool Sphere::getIntersection()
{
	return check.intersection;
}