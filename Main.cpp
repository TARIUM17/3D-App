#include <iostream>
#include "Utils.h"

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
		std::cout << "== Failing Creating Window ==";
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);  //select window

	gladLoadGL();    //Load OpneGL fiunctions using GLAD (for configuring links)
	//specify viewport window (from 0,0 to 800,600)
	glViewport(0, 0, 800, 600);

	glClearColor(0.10f, 0.22f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();  //All "poll" events with window (such as resizing and etc.)
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}