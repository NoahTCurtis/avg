#pragma once
#include "camera.h"
#include "manager.h"
#include "mesh.h"
#include "render.h"
#include "shader.h"
#include "window.h"

class Application
{
public:
	Application();
	bool Loop();
	~Application();

	Manager<Camera> Cameras;
	Manager<Mesh> Meshes;
	Manager<Renderer> Renders;
	Manager<Shader> Shaders;
	Manager<Window> Windows;
};

extern Application* app;