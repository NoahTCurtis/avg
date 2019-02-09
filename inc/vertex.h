#pragma once
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

typedef struct
{
    unsigned a;
    unsigned b;
} Edge;

class VertexForMesh
{
public:
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uv;
};