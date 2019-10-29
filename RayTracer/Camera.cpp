#include "Camera.h"

Ray Camera::generateRay(glm::ivec2 _pixelCoordinates, glm::ivec2 _windowSize)
{
	Ray myRay;

	mapping.x = (((float)_pixelCoordinates.x / _windowSize.x) * 2.0f) - 1.0f;
	mapping.y = (((float)_pixelCoordinates.y / _windowSize.y) * 2.0f) - 1.0f;

	nearPlane = glm::vec4(mapping.x, mapping.y, -1.0f, 1.0f);
	farPlane = glm::vec4(mapping.x, mapping.y, 1.0f, 1.0f);

	glm::vec3 origin = glm::vec3(_pixelCoordinates.x, _pixelCoordinates.y, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);

	myRay.origin = origin;
	myRay.direction = direction;

	return myRay;
}