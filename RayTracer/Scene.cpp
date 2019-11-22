#include "Scene.h"

Scene::Scene()
{

}

void Scene::initialise(glm::ivec2 _windowSize)
{
	windowSize = _windowSize;

	myCamera.initialise(glm::mat4(1), glm::perspective(0.7f, ((float)_windowSize.x / (float)_windowSize.y), 0.1f, 100.0f));
	mySphere.initialise(glm::vec3(-20.0f, 0.0f, -100.0f), 20.0f, 1.0f);
	mySphere2.initialise(glm::vec3(20.0f, 0.0f, -100.0f), 20.0f, 0.0f);

	myTracer.objects.push_back(mySphere);
	myTracer.objects.push_back(mySphere2);
}

glm::ivec2 Scene::getWindowSize()
{
	return windowSize;
}