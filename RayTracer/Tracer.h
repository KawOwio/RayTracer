#pragma once
#ifndef _TRACER_H_
#define _TRACER_H_

#include "MCG_GFX_Lib.h"
#include "Ray.h"
#include "Sphere.h"
#include "Geometry.h"

#include <vector>

class Tracer
{
public:
	glm::vec3 traceRay(Ray _myRay);
	std::vector<Sphere> objects;
};

#endif