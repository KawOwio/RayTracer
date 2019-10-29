#include "Ray.h"
#include <iostream>
Ray::Ray()
{

}

Ray::Ray(glm::vec3 _origin, glm::vec3 _direction)
{
	Ray::setOrigin(_origin);
	Ray::setDirection(_direction);

	//std::cout << "Ray Origin X: " << _origin.x << " Y: " << _origin.y << " Z: " << _origin.z <<  std::endl;
	//std::cout << "Ray Direction X: " << _direction.x << " Y: " << _direction.y << " Z: " << _direction.z <<  std::endl;
}

void Ray::setOrigin(glm::vec3 _origin)
{
	Ray::origin = _origin;
}

void Ray::setDirection(glm::vec3 _direction)
{
	Ray::origin = _direction;
}

glm::vec3 Ray::getOrigin()
{
	return Ray::origin;
}

glm::vec3 Ray::getDirection()
{
	return Ray::direction;
}