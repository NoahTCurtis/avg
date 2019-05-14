#include <direct.h>
#include <fstream>
#include <cassert>
#include <iostream>
#include <filesystem>

#include "file.h"

std::string get_current_working_directory(void)
{
	char buff[512];
	_getcwd(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

std::string strip_slashes(std::string str)
{
	if (str.length() <= 2)
		return str;
	auto front = str.begin();
	auto back = str.end() - 1;
	if (*front == '/' || *front == '\\')
		front += 1;
	if (*back == '/' || *back == '\\')
		back -= 1;
	return std::string(front, back + 1);
}

std::string get_full_file_path(std::string filename, std::string directory)
{
	/*
	std::string fullpath
		= std::string("\\..\\")
		+ strip_slashes(directory)
		+ '\\'
		+ strip_slashes(filename);
	return fullpath;
	*/

	///std::filesystem::path p;

}

std::string get_file_text(std::string filename, std::string directory)
{
	//FUNCTION NOT WORKING: RETURNING EMPTY STRINGS
	std::ifstream t(get_full_file_path(filename, directory));
	assert(t.good());
	return std::string((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
}