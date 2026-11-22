#include "ShaderClass.h"

// Error function. For error checking
void compileErrors(unsigned int shader, const char* type) {
	int hasFinished;
	char infoLog[1024];
	if (type != "PROGRAM") {	//Linker checker
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasFinished);
		if (!hasFinished) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << infoLog << "\n---\n";
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasFinished);
		if (!hasFinished) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << infoLog << "\n---\n";
		}
	}
}

// just reading
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

	//vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // ->
	//->      (shader, count, *char *string (text for shaders. Writed above), lenth (don't need it) )
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");
	
	//Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(vertexShader, "FRAGMENT");

	//Shader programm
	ID = glCreateProgram();
	//Attaching shaders to programm
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

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