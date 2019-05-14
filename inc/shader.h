#pragma once
#include <string>

class Shader
{
public:
	bool Deserialize(std::string vertFilename, std::string fragFilename);
	bool Deserialize();
	bool BuildAttach();
	void Bind();

	template<typename T>
	void setUniform(std::string name, T value);

private:
	std::string vertFilename_;
	std::string vertText_;

	std::string fragFilename_;
	std::string fragText_;

	int ID_ = -1;
};