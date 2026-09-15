#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils.h"

//set shader settings
//
static const char* vertex_shader_source = "#version 330\n"
"layout (location = 0) in vec3 aPos\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos, 1.0f);\n"          //vec4 (aPos.x, aPos.y, aPos.z, 1.0f)
"}\n";

static const char* fragment_shader_source = "#version 330\n"
"in vec3 color = vec3(0,8f, 0,3f, 0,02f);\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0f);\n"
"}\n";

struct Vertex {
	
}; 

void main() {
	//initialization of GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);


	//point out to use OpenGL 3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//using CORE meaning we using only modern functions of OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//creating and checking window state
	GLFWwindow* window = glfwCreateWindow(800, 600, "3D_Test", NULL, NULL);
	if (!window) {
		std::cout << "== Failing Creating Window ==";
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);  //select window

	gladLoadGL();    //Load OpneGL fiunctions using GLAD (for configuring links)
	//specify viewport window (from 0,0 to 800,600)
	glViewport(0, 0, 800, 600);
	
	//========================================================================//
	// SHADERS
	//========================================================================//
	{
		//Compile all shaders
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertex_shader_source, NULL); // ->
											//->      (shader, count, *char *string (text for shaders. Writed above), lenth (don't need it) )
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
		glCompileShader(fragmentShader);


		GLuint shaderProgram = glCreateProgram();
		//Attaching shaders to programm
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		//Deleting shaders 'cause they're already in programm 
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}


	//Clearing Collor Buffer
	glClearColor(0.23f, 0.23f, 0.23f, 1.0f); //background collor
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	while (!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();  //All "poll" events with window (such as window resizing and etc.)
	}

	//closing window and deleting
	glfwDestroyWindow(window);
	glfwTerminate();
}