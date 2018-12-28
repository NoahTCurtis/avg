#pragma once
#include "manager.h"
#include "camera.h"
#include "window.h"

class Application
{
public:
	Application();
	bool Loop();
	~Application();

	Manager<Camera> Cameras;
	Manager<Window> Windows;
};