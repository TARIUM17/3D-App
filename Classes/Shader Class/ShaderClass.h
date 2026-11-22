#pragma once
#include "BasicLibs.h"

std::string getFileContent(const char* file);
void compileErrors(unsigned int shader, const char* type);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);
	void Activate();
	void Delete();
};