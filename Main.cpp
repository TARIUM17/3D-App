#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils.h"

//set shader settings
//
static const char* vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos, 1.0f);\n"
"}\n";

static const char* fragment_shader_source = "#version 330 core\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
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
		std::cout << "== Failing creating window ==";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);  //select window

	if(!gladLoadGL())    //Load OpneGL fiunctions using GLAD (for configuring links)
	{
		std::cout << "== Failed to initialize GLAD ==";
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//specify viewport window (from 0,0 to 800,600)
	glViewport(0, 0, 800, 600);

	//========================================================================//
	// SHADERS
	//========================================================================//

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


	//========================================================================//
	// VERTEX OBJECT
	//========================================================================//

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //before binding buffer (for me: "You're stupid")

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);      // ->
	// -> (vertex shader index, data size (3 for vertex - x,y,z), type, normallize (for GL_INT), stride between data for each verteces, pointer to the beggining of the data in the array)
	
	//removing current VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 0 - index in vertex attribute - layout (location = x) in SORCE vertex shader
	glEnableVertexAttribArray(0); // index in array


	//========================================================================//
	// WINDOW
	//========================================================================//

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.23f, 0.23f, 0.23f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();  //All "poll" events with window (such as window resizing and etc.)
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//closing window and deleting
	glfwDestroyWindow(window);
	glfwTerminate();
}