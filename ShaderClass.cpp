#include "ShaderClass.h"

std::string getFileContent(const char* file) {
	std::ifstream in(file, std::ios::in | std::ios::binary);
	if (!in.is_open()) {
		int errorCode = errno;
		throw std::system_error(errorCode, std::generic_category(), "Failed to open file: " + std::string(file));
	}
	std::string content;

	in.seekg(0, std::ios::end);
	content.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&content[0], content.size());
	in.close();

	return(content);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = getFileContent(vertexFile);
    std::string fragmentCode = getFileContent(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

	//Compile all shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // ->
	//->      (shader, count, *char *string (text for shaders. Writed above), lenth (don't need it) )
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);


	ID = glCreateProgram();
	//Attaching shaders to programm
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	//Deleting shaders 'cause they're already in programm 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}