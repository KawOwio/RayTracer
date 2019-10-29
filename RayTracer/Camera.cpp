#include "Camera.h"

Ray Camera::generateRay(glm::ivec2 _pixelCoordinates)
{
	glm::vec3 origin = glm::vec3(_pixelCoordinates.x, _pixelCoordinates.y, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);

	myRay.setOrigin(origin);
	myRay.setDirection(direction);

	return myRay;
}