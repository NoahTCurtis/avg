#include <cassert>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "window.h"
#include "input.h"

std::map<GLFWwindow*, Window*> Window::lookupTable_;

void Window::Initialize(int vertical, int horizontal, const char* title)
{
	//hint what kind of window we want
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	///glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	///glfwWindowHint(GLFW_DECORATED, false);

	//make new window
	window_ = glfwCreateWindow(horizontal, vertical, title, NULL, NULL);
	assert(window_ != nullptr);
	lookupTable_[window_] = this;

	glfwMakeContextCurrent(window_);
	////glViewport(0, 0, horizontal, vertical); //this got moved
}


void Window::Register()
{
	///glfwSetWindowSizeCallback(window_, WindowSizeCallback);
	///glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
	Input->RegisterWindow(window_);
}

Window::~Window()
{
	lookupTable_.erase(window_);
	glfwDestroyWindow(window_);
}


void Window::change_title(std::string title)
{
	glfwSetWindowTitle(window_, title.c_str());
}


void Window::set_size(int width, int height)
{
	glfwSetWindowSize(window_, width, height);
	glViewport(0, 0, width, height);
}


glm::vec2 Window::get_size()
{
	int x, y;
	glfwGetWindowSize(window_, &x, &y);
	return glm::vec2(x, y);
}

glm::mat4 Window::compute_perspective_matrix(float znear, float zfar)
{
	glm::vec2 size = get_size();
	perspective_ = glm::perspective(glm::pi<float>() / 2.0f, size.x / size.y, znear, zfar);
	return perspective_;
}

Window * Window::LookupWindowByGLFWwindow(GLFWwindow * gw)
{
	Window* w = lookupTable_[gw];
	assert(w != nullptr);
	return w;
}

///////////////////////////////////////////////////////////////////////////////////

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window::LookupWindowByGLFWwindow(window)->set_size(width, height);
}