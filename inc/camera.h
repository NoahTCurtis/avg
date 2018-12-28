#pragma once
#include "glm/glm.hpp"

class Camera
{
public:
	glm::vec3 position = glm::vec3(3, 2, 3);
	glm::vec3 look = glm::vec3(0, 1, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);
};