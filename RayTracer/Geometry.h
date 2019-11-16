#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Sphere.h"

//A structure to return both bool if there was an intersection and
//distance from the the intersection to a shortest point on line from an object's centre 
//and coordinates of intersection
struct intersectionReturn
{
	float distance;
	bool intersection;
	glm::vec3 intersectionPoint;
};

class Geometry
{
private:
	intersectionReturn check;

public:
	intersectionReturn intersection(Ray _myRay, Sphere _mySphere);
};

#endif // !_GEOMETRY_H_