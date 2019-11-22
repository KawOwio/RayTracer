#pragma once
#ifndef _RAY_H_
#define _RAY_H_

#include "MCG_GFX_Lib.h"

class Ray
{
private:

public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray();
	//Ray(glm::vec3 _origin, glm::vec3 _direction);
};

#endif