#pragma once
#include <string>

class Shader
{
public:
	bool Deserialize(std::string vertFilename, std::string fragFilename);
	bool Deserialize();
	bool BuildAttach();

	std::string vertFilename;
	bool vertIsValid;

	std::string fragFilename;
	bool fragIsValid;

private:
	std::string vertText;
	std::string fragText;
};