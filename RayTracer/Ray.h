#ifndef _RAY_H_
#define _RAY_H_

#include "MCG_GFX_Lib.h"

class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray();
	Ray(glm::vec3 _origin, glm::vec3 _direction);

	void setOrigin(glm::vec3 _origin);
	void setDirection(glm::vec3 _direction);

	glm::vec3 getOrigin();
	glm::vec3 getDirection();
};

#endif