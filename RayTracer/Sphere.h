#pragma once
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "MCG_GFX_Lib.h"
#include "Ray.h"

class Sphere
{
private:
	glm::vec3 centre;
	float radius;
	glm::vec3 surfaceNormal;

public:
	Sphere(glm::vec3 _centre, float _radius);
	glm::vec3 shadePixel(Ray _myRay, glm::vec3 _intersectionPoint);

	glm::vec3 getCentre();
	float getRadius();
};

#endif