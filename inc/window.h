#pragma once

#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class Window
{
public:
	void Initialize(int vertical, int horizontal, const char* title);
	void Register();
	~Window();

	GLFWwindow* getGLFWwindow() { return window_; }
	void MakeContextCurrent();

	void set_title(std::string title);
	void set_size(int width, int height);
	glm::vec2 get_size();
	glm::mat4 compute_perspective_matrix(float znear, float zfar);

	static Window* LookupWindowByGLFWwindow(GLFWwindow* gw);

private:
	static std::map<GLFWwindow*, Window*> lookupTable_;
	GLFWwindow* window_;
	glm::mat4 perspective_;
};


//GLFW callbacks.
//Naming convention is just strip off leading "GLFW"
//char/key/input callbacks should remember to passthrough to imgui
void WindowSizeCallback(GLFWwindow* window, int width, int height);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);