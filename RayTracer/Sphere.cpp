#include "Geometry.h"
#include "Sphere.h"

Sphere::Sphere(glm::vec3 _centre, float _radius)
{
	centre = _centre;
	radius = _radius;
}

glm::vec3 Sphere::shadePixel(Ray _myRay, glm::vec3 _intersectionPoint)
{
	Geometry geometry;

	glm::vec3 lightPos = glm::vec3(200.0f, -200.0f, 200.0f);

	glm::vec3 lightDirection = glm::normalize(-(_intersectionPoint)+lightPos);

	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 diffuseColour = glm::vec3(1.0f, 0.62f, 0.44f);
	//glm::vec3 diffuseColour = glm::vec3(0.64f, 1.0f, 0.64f);
	glm::vec3 normal = geometry.sphereNormal(centre, _intersectionPoint);

	glm::vec3 colour = glm::max(glm::dot(lightDirection, normal), 0.0f) * lightColour * diffuseColour;

	return colour;
}

glm::vec3 Sphere::getCentre()
{
	return centre;
}

float Sphere::getRadius()
{
	return radius;
}