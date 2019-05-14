#include <iostream>

#include "glad/glad.h"

#include "shader.h"
#include "file.h"

bool Shader::Deserialize(std::string vertFilename, std::string fragFilename)
{
	vertFilename_ = vertFilename;
	fragFilename_ = fragFilename;
	return Deserialize();
}

bool Shader::Deserialize()
{
	vertText_ = get_file_text(vertFilename_, "res/shaders");
	fragText_ = get_file_text(fragFilename_, "res/shaders");
	return false;
}

bool Shader::BuildAttach()
{
	unsigned int vertexID, fragmentID;
	int vertSuccess, fragSuccess, shaderSuccess;
	char infoLog[512];

	// vertex Shader
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	const char* vertCodePtr = vertText_.c_str();
	glShaderSource(vertexID, 1, &vertCodePtr, nullptr);
	glCompileShader(vertexID);
	// print compile errors if any
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &vertSuccess);
	if (!vertSuccess)
	{
		glGetShaderInfoLog(vertexID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// similiar for Fragment Shader
	// fragment Shader
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragCodePtr = fragText_.c_str();
	glShaderSource(fragmentID, 1, &fragCodePtr, nullptr);
	glCompileShader(fragmentID);
	// print compile errors if any
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &fragSuccess);
	if (!fragSuccess)
	{
		glGetShaderInfoLog(vertexID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// shader Program
	ID_ = glCreateProgram();
	glAttachShader(ID_, vertexID);
	glAttachShader(ID_, fragmentID);
	glLinkProgram(ID_);
	// print linking errors if any
	glGetProgramiv(ID_, GL_LINK_STATUS, &shaderSuccess);
	if (!shaderSuccess)
	{
		glGetProgramInfoLog(ID_, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	return vertSuccess && fragSuccess && shaderSuccess;
}

void Shader::Bind()
{
	glUseProgram(ID_);
}

///////////////////////////////////////////////////////////////////////////////
// SET UNFORMS

template<> void Shader::setUniform<bool>(std::string name, bool value)
{
	glUniform1i(glGetUniformLocation(ID_, name.c_str()), (int)value);
}

template<> void Shader::setUniform<int>(std::string name, int value)
{
	glUniform1i(glGetUniformLocation(ID_, name.c_str()), value);
}

template<> void Shader::setUniform<float>(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(ID_, name.c_str()), value);
}



