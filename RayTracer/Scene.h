#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Tracer.h"
#include "Ray.h"
#include "Sphere.h"
#include "Geometry.h"

//Class which initialises all other classes
//Made for easy passing variables across functions
class Scene
{
public:
	Geometry geometry;
	intersectionReturn intersectionResult;
	intersectionReturn tempResult;	//temporary solution for reflections
	Camera myCamera;
	Tracer myTracer;
	Ray myRay;
	Ray myReflectionRay;
	Sphere mySphere;
	Sphere mySphere2;
	Sphere mySphere3;

	void initialise(glm::vec2 _windowSize);
	glm::vec2 getWindowSize();

private:
	glm::vec2 windowSize;
};

#endif // !_SCENE_H_