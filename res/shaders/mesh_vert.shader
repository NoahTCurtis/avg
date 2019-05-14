#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;

out vec3 outColor;
out vec2 outTexCoord;

void main()
{
    gl_Position = vec4(inPos, 1.0);
    ourColor = inColor;
    TexCoord = inTexCoord;
}