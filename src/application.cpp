#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "application.h"
#include "input.h"


void debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam);

Application::Application()
{

	//Create Managers
	Input = new InputManager;
	Input->Initialize();

	//Initialize GLFW
	glfwInit();

	//Create a window, set context to current
	Windows.CreateMember(0);
	Windows[0].Initialize(600, 800, "Another Voxel Game");
	
	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert(false);
	}
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST); //this should maybe be somewhere else?

	//TODO: FIX THE DEBUG CALLBACK FOR CHRISTS SAKE
	///glDebugMessageCallback(debug_callback, nullptr); 

	Windows[0].Register();

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io; //just to initialize the singleton
	ImGui_ImplGlfw_InitForOpenGL(Windows[0].getGLFWwindow(), false); //only the main window will have imgui
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark(); //already the default
}

bool Application::Loop()
{
	//Imgui real quick
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
		ImGui::Begin("Editor");
			static glm::vec3 clearColor(0.8f, 0.3f, 0.1f);
			ImGui::ColorEdit3("clear color", (float*)&clearColor.x);
		ImGui::End();
	ImGui::Render();

	//update systems
	Input->Update(0);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//finish and flush commands
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(Windows[0].getGLFWwindow());

	if (Input->IsTriggered(Keys::W))
	{
		unsigned key = Windows.CreateMember();
		std::string name = std::string("window ") + std::to_string(key);
		Windows[key].Initialize(600, 800, name.c_str());
		Windows[key].Register();
	}

	
	return !Input->IsTriggered(Keys::Escape) && !glfwWindowShouldClose(Windows[0].getGLFWwindow());
}

Application::~Application()
{
	/*
	// Cleanup imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//Exit safely
	delete mainWindow;
	glfwTerminate();
	return 0;
	//*/
}



void debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	std::cout << "Error: OpenGL reported an error from " << source << ". Type: " << type << " ID: " << id << " Severity: " << severity << std::endl;
	std::cout << message << std::endl;
}