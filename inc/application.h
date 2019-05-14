#pragma once

#include <chrono>

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

	double time_elapsed = 0;
	float dt = 0;
private:
	//This is the previous frame's "now" time_point
	std::chrono::time_point<std::chrono::steady_clock> then_;
};

extern Application* app;

void debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam);