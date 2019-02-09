#pragma once

#include <string>
#include <list>
#include <vector>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "vertex.h"

class Mesh
{
public:
    Mesh();
    Mesh(std::string filename);
    ~Mesh();

    void create_default_mesh(); //(TEMP)
    ///void create_from_obj(std::string filename);
    void create_VAO_from_raw_data(std::vector<VertexForMesh>& vertices, std::vector<unsigned>& indices);
    void randomize_vertex_colors(std::vector<VertexForMesh>& verts);
    void bind();

    std::string name;
    unsigned vertCount = -1;
    unsigned indexCount = -1;
    bool visible = false;
private:
    GLuint VBO_name = -1;
    GLuint VAO_name = -1;
    GLuint EBO_name = -1;

};

extern std::list<Mesh*> Meshes;