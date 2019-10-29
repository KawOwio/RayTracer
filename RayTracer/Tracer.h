#ifndef _TRACER_H_
#define _TRACER_H_

#include "MCG_GFX_Lib.h"
#include "Ray.h"

class Tracer
{
public:
	glm::ivec3 traceRay(Ray _myRay);
};

#endif