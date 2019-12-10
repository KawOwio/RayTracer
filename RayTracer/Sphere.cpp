#include "Sphere.h"
#include "Geometry.h"

Sphere::Sphere()
{

}

void Sphere::initialise(glm::vec3 _centre, float _radius, float _reflectivity)
{
	centre = _centre;
	radius = _radius;
	reflectivity = _reflectivity;
}

glm::vec3 Sphere::shadePixel(Ray _myRay, glm::vec3 _intersectionPoint)
{
	Geometry geometry;

	glm::vec3 lightDirection = glm::normalize(-(_intersectionPoint)+lightPos);
	glm::vec3 H = (worldOrigin + lightPos) / glm::length(worldOrigin + lightPos);

	surfaceNormal = geometry.sphereNormal(centre, _intersectionPoint);

	if (glm::dot(lightDirection, surfaceNormal) > 0)
	{
		facing = 1.0f;
	}
	else
	{
		facing = 0.0f;
	}
	
	//if (reflectivity > 0.0f)
	//{
	//	glm::vec3 reflectionRayDirection = glm::reflect(_intersectionPoint, surfaceNormal);
	//	//glm::vec3 reflectionRayDirection = _intersectionPoint - 2.0f * surfaceNormal * glm::dot(surfaceNormal, _intersectionPoint);
	//	_myRay.origin = _intersectionPoint;
	//	_myRay.direction = reflectionRayDirection;

	//	glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);
	//	return colour * specularColour;
	//}
	

	glm::vec3 diffusive = (glm::max(glm::dot(lightDirection, surfaceNormal), 0.0f) * lightColour * diffuseColour);
	glm::vec3 specular = (glm::pow(glm::max(glm::dot(H, surfaceNormal), 0.0f), shinines) * lightColour * specularColour * facing);

	glm::vec3 colour = glm::min((diffusive + specular), 1.0f);	

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

float Sphere::getReflectivity()
{
	return reflectivity;
}

void Sphere::setDiffuse(glm::vec3 _diffuse)
{
	diffuseColour = _diffuse;
}

void Sphere::setSpecular(glm::vec3 _specular)
{
	specularColour = _specular;
}