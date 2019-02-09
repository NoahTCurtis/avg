#pragma once
#include "glm/glm.hpp"

class Renderer
{
public:
	

	void Render();

	glm::vec3 clearColor = glm::vec3(0.8f, 0.3f, 0.1f);
	unsigned windowIndex = 0; //index into app's window manager
	unsigned cameraIndex = 0; //index into app's camera manager
};