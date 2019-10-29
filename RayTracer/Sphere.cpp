#include "Sphere.h"

glm::ivec3 Sphere::shadePixel(Ray _myRay, glm::vec3 _intersectionPoint)
{
	return glm::ivec3(255, 0, 0);
}

intersectionReturn Sphere::intersection(Ray _myRay, glm::vec3 _queryPoint)
{
	float d;
	
	glm::vec3 rayOrigin = _myRay.getOrigin();
	glm::vec3 rayDirection = _myRay.getDirection();
	glm::vec3 worldOrigin = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 a = rayOrigin;
	glm::vec3 P = _queryPoint;
	glm::vec3 Pa = P - a;
	glm::vec3 n = rayDirection;
	glm::vec3 X;
	
	d = glm::length(Pa - (glm::dot(Pa, n) * n));

	if (radius >= d)
	{
		check.distance = glm::sqrt(glm::pow(radius, 2) - glm::pow(d, 2));
		check.intersection = true;
	}
	else if(radius < d)
	{
		check.distance = 0.0f;
		check.intersection = false;
	}

	return check;
}

bool Sphere::getIntersection()
{
	return check.intersection;
}