
#include "BasicLibs.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

GLfloat vertices[] = {
	//basic verteces
	-0.5f, -0.5f, 0.0f, //bottom-left
	0.5f, -0.5f, 0.0f, //bottom-right
	0.0f, 0.5f, 0.0f, //top

	//additionals verteces
	0.0f, -0.5f, 0.0f, //bottom
	-0.5f / 2, 0.0f, 0.0f, //left-middle
	0.5f / 2, 0.0f, 0.0f //right-middle
};

GLuint indices[]{
	0, 4, 3, //bottom-left triangle
	3, 1, 5, //bottom-right triangle
	4, 5, 2 //top triangle
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

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();

	//========================================================================//
	// WINDOW
	//========================================================================//

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.23f, 0.23f, 0.23f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();  //All "poll" events with window (such as window resizing and etc.)
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	//closing window and deleting
	glfwDestroyWindow(window);
	glfwTerminate();
}