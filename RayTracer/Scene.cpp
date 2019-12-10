#include "Scene.h"

Scene::Scene()
{

}

void Scene::initialise(glm::ivec2 _windowSize)
{
	windowSize = _windowSize;

	myCamera.initialise(glm::mat4(1), glm::perspective(0.7f, ((float)_windowSize.x / (float)_windowSize.y), 0.1f, 100.0f));
	mySphere.initialise(glm::vec3(-2.0f, 0.0f, -10.0f), 2.0f, 0.07f);
	mySphere2.initialise(glm::vec3(2.0f, 0.0f, -10.0f), 2.0f, 0.0f);

	mySphere.setDiffuse(glm::vec3(0.67f, 0.29f, 0.52f));
	mySphere.setSpecular(glm::vec3(0.76f, 0.22f, 0.78f));

	myTracer.objects.push_back(mySphere);
	myTracer.objects.push_back(mySphere2);
}

glm::ivec2 Scene::getWindowSize()
{
	return windowSize;
}