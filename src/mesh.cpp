#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "mesh.h"
#include "vertex.h"

std::list<Mesh*> Meshes;

Mesh::Mesh()
{
	
}


Mesh::Mesh(std::string filename)
{
	///create_from_obj(filename);
	///name = std::string(filename.begin(), filename.end() - 4);
}


Mesh::~Mesh()
{
	glBindVertexArray(VAO_name);
	glDeleteBuffers(1, &VBO_name);
	glDeleteBuffers(1, &EBO_name);
	glDeleteVertexArrays(1, &VAO_name);
}


VertexForMesh default_vertices[] = {
	{ {0.5f,   0.5f, 0.0f},  {1.0, 0.0, 0.0}, {0.0, 0.0} }, // top right
	{ {0.5f,  -0.5f, 0.0f},  {0.0, 1.0, 0.0}, {0.0, 1.0} }, // bottom right
	{ {-0.5f, -0.5f, 0.0f},  {0.0, 0.0, 1.0}, {1.0, 0.0} }, // bottom left
	{ {-0.5f,  0.5f, 0.0f},  {0.0, 0.0, 0.0}, {1.0, 1.0} }  // top left 
};
unsigned int default_indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};


void Mesh::create_default_mesh()
{
	std::vector<VertexForMesh> vertices;
	std::vector<unsigned> indices;
	for (int i = 0; i < 4; i++)
		vertices.push_back(default_vertices[i]);
	for (int i = 0; i < 6; i++)
		indices.push_back(default_indices[i]);
	create_VAO_from_raw_data(vertices, indices);
}


void Mesh::create_VAO_from_raw_data(std::vector<VertexForMesh>& vertices,
									std::vector<unsigned>& indices)
{
	assert(VAO_name == -1);

	//Generate and bind VAO
	glGenVertexArrays(1, &VAO_name);
	glBindVertexArray(VAO_name);

	//Generate and bind and allocate/fill the VBO
	glGenBuffers(1, &VBO_name);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_name);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexForMesh), &vertices[0], GL_STATIC_DRAW);

	//Generate and bind and allocate/fill the EBO
	glGenBuffers(1, &EBO_name);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_name);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	//Inform OpenGL of what the vert data is
		//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexForMesh), (void*)0);
	glEnableVertexAttribArray(0);
		//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexForMesh), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
		//UV attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexForMesh), (void*)(6 * sizeof(float)));

	vertCount = (unsigned)vertices.size();
	indexCount = (unsigned)indices.size();
}


void Mesh::bind()
{
	glBindVertexArray(VAO_name);
}


void Mesh::randomize_vertex_colors(std::vector<VertexForMesh>& verts)
{
	///for (auto& vert : verts)
	///    vert.color = glm::vec3(randFloat01(), randFloat01(), randFloat01());
}
