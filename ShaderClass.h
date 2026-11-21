#pragma once
#include "BasicLibs.h"

std::string getFileContent(const char* file);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);
	void Activate();
	void Delete();

};