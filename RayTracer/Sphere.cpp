#include "Sphere.h"

Sphere::Sphere(glm::vec3 _centre, float _radius)
{
	centre = _centre;
	radius = _radius;
}

glm::ivec3 Sphere::shadePixel(Ray _myRay, glm::vec3 _intersectionPoint)
{
	return glm::ivec3(255, 0, 0);
}

glm::vec3 Sphere::getCentre()
{
	return centre;
}

float Sphere::getRadius()
{
	return radius;
}