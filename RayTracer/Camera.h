#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"
#include "MCG_GFX_Lib.h"

class Camera
{
private:
	glm::vec4 nearPlane;
	glm::vec4 farPlane;
	glm::vec2 mapping;

	glm::mat4 viewMatrix;			//To represent the camera's position and orientation
	glm::mat4 projectionMatrix;		//To act like the camera's lens

public:	
	void initialise(glm::mat4 _view, glm::mat4 _projection);
	Ray generateRay(glm::vec2 _pixelCoordinates, glm::vec2 _windowSize);
};

#endif