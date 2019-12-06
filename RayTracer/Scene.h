#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Tracer.h"
#include "Ray.h"
#include "Sphere.h"
#include "Geometry.h"

class Scene
{
public:
	Scene();

	Geometry geometry;
	intersectionReturn intersectionResult;
	Camera myCamera;
	Tracer myTracer;
	Ray myRay;
	Ray myReflectionRay;
	Sphere mySphere;
	Sphere mySphere2;

	void initialise(glm::ivec2 _windowSize);
	glm::ivec2 getWindowSize();

private:
	glm::ivec2 windowSize;
};

#endif // !_SCENE_H_