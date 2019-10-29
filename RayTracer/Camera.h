#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"
#include "MCG_GFX_Lib.h"

class Camera
{
private:
	Ray myRay;
public:
	Ray generateRay(glm::ivec2 _pixelCoordinates);
};

#endif