#pragma once

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "MCG_GFX_Lib.h"
#include "Ray.h"

//A structure to return both bool if there was an intersection and
//distance from the the intersection to a shortest point on line from an object's centre 
struct intersectionReturn
{
	float distance;
	bool intersection;
	glm::vec3 intersectionPoint;
};

class Sphere
{
private:
	intersectionReturn check;
	glm::vec3 centre = glm::vec3(0.0f, 0.0f, -200.0f);
	float radius = 50.0f;
public:
	glm::ivec3 shadePixel(Ray _myRay, glm::vec3 _intersectionPoint);
	intersectionReturn intersection(Ray _myRay);

	bool getIntersection();
};

#endif