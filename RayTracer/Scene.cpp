#include "Scene.h"

Scene::Scene()
{

}

void Scene::initialise(glm::ivec2 _windowSize)
{
	windowSize = _windowSize;

	myCamera.initialise(glm::mat4(1), glm::perspective(0.7f, ((float)_windowSize.x / (float)_windowSize.y), 0.1f, 100.0f));
	mySphere.initialise(glm::vec3(-2.0f, 0.0f, -10.0f), 2.0f, 1.0f);
	mySphere2.initialise(glm::vec3(2.0f, 0.0f, -10.0f), 2.0f, 0.0f);

	mySphere.setDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	mySphere.setSpecular(glm::vec3(0.25f, 0.25f, 0.25f));

	myTracer.objects.push_back(mySphere);
	myTracer.objects.push_back(mySphere2);
}

glm::ivec2 Scene::getWindowSize()
{
	return windowSize;
}