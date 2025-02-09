#include "Camera.h"

void Camera::initialise(glm::mat4 _view, glm::mat4 _projection)
{
	viewMatrix = _view;
	projectionMatrix = _projection;
}

Ray Camera::generateRay(glm::vec2 _pixelCoordinates, glm::vec2 _windowSize)
{
	Ray myRay;

	//Mapping coordinates
	mapping.x = (((float)_pixelCoordinates.x / (float)_windowSize.x) * 2.0f) - 1.0f;
	mapping.y = (((float)_pixelCoordinates.y / (float)_windowSize.y) * 2.0f) - 1.0f;

	nearPlane = glm::vec4(mapping.x, mapping.y, -1.0f, 1.0f);
	farPlane = glm::vec4(mapping.x, mapping.y, 1.0f, 1.0f);

	//Applying inverse projection matrix
	nearPlane = glm::inverse(projectionMatrix) * nearPlane;
	farPlane = glm::inverse(projectionMatrix) * farPlane;

	nearPlane /= nearPlane.w;
	farPlane /= farPlane.w;

	//Applying inverse view matrix
	nearPlane = glm::inverse(viewMatrix) * nearPlane;
	farPlane = glm::inverse(viewMatrix) * farPlane;

	glm::vec3 origin = glm::vec3(nearPlane.x, nearPlane.y, nearPlane.z);
	glm::vec3 direction = glm::normalize(glm::vec3(farPlane.x, farPlane.y, farPlane.z) - origin);

	myRay.origin = origin;
	myRay.direction = direction;

	//Check if a ray is in front of the camera
	if (myRay.direction.z >= 0.0f)
	{
		myRay.direction.z = myRay.direction.z;
	}

	return myRay;
}