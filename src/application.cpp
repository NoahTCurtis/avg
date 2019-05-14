#include <iostream>
#include <string>
#include <cassert>
#include <ctime>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "application.h"
#include "input.h"
#include "mesh.h"

Application* app = nullptr;

Application::Application()
{
	//Initialize RNG
	srand( static_cast<int>( time(0) ) );

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
	glDebugMessageCallback(debug_callback, nullptr); 

	//register window's glfw and imgui callbacks
	Windows[0].Register();

	//create a default renderer and camera
	Cameras.CreateMember(0);
	Renders.CreateMember(0);
	Renders[0].windowIndex = 0; //this renderer is tied to the main window
	Renders[0].cameraIndex = 0; //this renderer uses the main camera

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io; //just to initialize the singleton
	ImGui_ImplGlfw_InitForOpenGL(Windows[0].getGLFWwindow(), false); //only the main window will have imgui
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark(); //already the default

	//(TEMP) SLAP IN A QUICK MESH (TEMP)
	Meshes[Meshes.CreateMember()].create_default_mesh();
	//(TEMP) Slap in a quick shader (TEMP)
	unsigned shaderID = Shaders.CreateMember(0);
	Shaders[shaderID].Deserialize("mesh_vert.shader", "mesh_frag.shader");
	Shaders[shaderID].BuildAttach();
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

	//Compute dt
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> delta = now - then_;
	dt = (float)delta.count();
	time_elapsed += dt;
	then_ = now;

	//update systems
	Input->Update(0);

	//render
	Renders[0].Render();

	//(TEMP) do something really stupid
	int w = 800 + static_cast<int>(static_cast<float>(glm::sin(time_elapsed) * 400.0));
	int h = 600 + static_cast<int>(static_cast<float>(glm::cos(time_elapsed) * 300.0));
	///Windows[0].set_size(w, h);
	Windows[0].set_title(std::string("Another Voxel Game (") + std::to_string(1.0f/dt) + ")");

	//return whether the app should continue
	return !Input->IsTriggered(Keys::Escape) && !glfwWindowShouldClose(Windows[0].getGLFWwindow());
}

Application::~Application()
{
	// Cleanup imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//Exit safely
	///delete mainWindow;
	glfwTerminate();
}



void debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	std::cout << "Error: OpenGL reported an error from " << source << ". Type: " << type << " ID: " << id << " Severity: " << severity << '\n';
	std::cout << message << std::endl;
}