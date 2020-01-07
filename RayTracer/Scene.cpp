#include "Scene.h"

void Scene::initialise(glm::vec2 _windowSize)
{
	windowSize = _windowSize;

	myCamera.initialise(glm::mat4(1), glm::perspective(0.7f, ((float)_windowSize.x / (float)_windowSize.y), 0.1f, 100.0f));
	mySphere.initialise(glm::vec3(-2.0f, -1.0f, -10.0f), 2.0f, 0.1f);
	mySphere2.initialise(glm::vec3(2.0f, -1.0f, -10.0f), 2.0f, 0.0f);
	mySphere3.initialise(glm::vec3(0.0f, 1.5f, -7.0f), 2.0f, 0.35f);

	mySphere.setDiffuse(glm::vec3(0.67f, 0.29f, 0.52f));
	mySphere.setSpecular(glm::vec3(0.76f, 0.22f, 0.78f));

	mySphere2.setDiffuse(glm::vec3(1.0f, 0.62f, 0.44f));
	mySphere2.setSpecular(glm::vec3(0.0f, 0.0f, 0.0f));

	mySphere3.setDiffuse(glm::vec3(0.67f, 0.67f, 0.67f));
	mySphere3.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

	myTracer.objects.push_back(mySphere);
	myTracer.objects.push_back(mySphere2);
	myTracer.objects.push_back(mySphere3);
}

glm::vec2 Scene::getWindowSize()
{
	return windowSize;
}