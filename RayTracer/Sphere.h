#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "MCG_GFX_Lib.h"
#include "Ray.h"

class Sphere
{
private:
	glm::vec3 centre;
	glm::vec3 surfaceNormal;
	//glm::vec3 lightPos = glm::vec3(0.0f, -20.0f, 20.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, -20.0f, 20.0f);
	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 diffuseColour = glm::vec3(1.0f, 0.62f, 0.44f);
	glm::vec3 specularColour = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 worldOrigin = glm::vec3(0.0f, 0.0f, 0.0f);

	float shinines = 100.0f;
	float reflectivity;
	float facing;
	float radius;

public:
	Sphere();
	void initialise(glm::vec3 _centre, float _radius, float _reflectivity);
	glm::vec3 shadePixel(Ray _myRay, glm::vec3 _intersectionPoint);

	glm::vec3 getCentre();
	float getRadius();
	float getReflectivity();

	void setDiffuse(glm::vec3 _diffuse);
	void setSpecular(glm::vec3 _specular);

	float distanceFromCamera;
};

#endif