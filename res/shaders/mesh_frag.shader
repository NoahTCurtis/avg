#version 330 core
in vec3 inColor;
in vec2 inTexCoord;
  
out vec4 outFragColor;

uniform sampler2D ourTexture;

void main()
{
    //outFragColor = texture(ourTexture, inTexCoord);
    outFragColor = vec4(inColor, 1.0f);
}