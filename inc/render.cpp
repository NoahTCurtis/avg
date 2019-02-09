#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "render.h"
#include "application.h"

void Renderer::Render()
{
	//Get my window
	Window& win = app->Windows[windowIndex];
	GLFWwindow* gwin = win.getGLFWwindow();
	win.MakeContextCurrent();
	
	//clear
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render goes here
	auto meshes = app->Meshes.GetMemberMap();
	for (auto& pair : meshes)
	{
		Mesh* mesh = pair.second;

		mesh->bind();
		///glm::mat4 model2world = mesh->get_model_to_world_matrix();
		///glUniformMatrix4fv(glGetUniformLocation(Globals.mesh_shader_program_name, "model2world"), 1, GL_FALSE, &model2world[0][0]);
		glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
	}

	//finish and flush commands
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(gwin);
}
