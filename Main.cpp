
#include "BasicLibs.h"
#include "Camera.h"
#include "ShaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

GLfloat vertices[] = {
	// Positions          // Normals            // Texture Coords
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // 0
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // 1
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // 2
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // 3

	// front
	-0.5f, -0.5f,  0.5f,   0.0f,  0.447f, 0.894f,  0.0f, 0.0f, // 4
	 0.5f, -0.5f,  0.5f,   0.0f,  0.447f, 0.894f,  1.0f, 0.0f, // 5
	 0.0f,  0.5f,  0.0f,   0.0f,  0.447f, 0.894f,  0.5f, 1.0f, // 6

	// right
	 0.5f, -0.5f,  0.5f,   0.894f, 0.447f, 0.0f,   0.0f, 0.0f, // 7
	 0.5f, -0.5f, -0.5f,   0.894f, 0.447f, 0.0f,   1.0f, 0.0f, // 8
	 0.0f,  0.5f,  0.0f,   0.894f, 0.447f, 0.0f,   0.5f, 1.0f, // 9
	 
	// back
	 0.5f, -0.5f, -0.5f,   0.0f,  0.447f, -0.894f, 0.0f, 0.0f, // 10
	-0.5f, -0.5f, -0.5f,   0.0f,  0.447f, -0.894f, 1.0f, 0.0f, // 11
	 0.0f,  0.5f,  0.0f,   0.0f,  0.447f, -0.894f, 0.5f, 1.0f, // 12
	
	 // left
	-0.5f, -0.5f, -0.5f,  -0.894f, 0.447f, 0.0f,   0.0f, 0.0f, // 13
	-0.5f, -0.5f,  0.5f,  -0.894f, 0.447f, 0.0f,   1.0f, 0.0f, // 14
	 0.0f,  0.5f,  0.0f,  -0.894f, 0.447f, 0.0f,   0.5f, 1.0f  // 15
};

GLuint indices[]{
	//bottom
	0, 1, 2,
	0, 2, 3,
	//sides
	4, 5, 6,
	7, 8, 9,
	10, 11, 12,
	13, 14, 15
};

GLfloat lightVertices[] = {
	-0.1f, -0.1f,  0.1f, // 0
	-0.1f, -0.1f, -0.1f, // 1
	 0.1f, -0.1f, -0.1f, // 2
	 0.1f, -0.1f,  0.1f, // 3
	-0.1f,  0.1f,  0.1f, // 4
	-0.1f,  0.1f, -0.1f, // 5
	 0.1f,  0.1f, -0.1f, // 6
	 0.1f,  0.1f,  0.1f  // 7
};

GLuint lightIndices[] = {
0, 1, 2,  2, 3, 0, // front
1, 5, 6,  6, 2, 1, // right
5, 4, 7,  7, 6, 5, // back
4, 0, 3,  3, 7, 4, // left
4, 5, 1,  1, 0, 4, // bottom
3, 2, 6,  6, 7, 3  // up
};

unsigned int width = 800;
unsigned int height = 800;

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
	GLFWwindow* window = glfwCreateWindow(width, height, "3D_Test", NULL, NULL);
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

	//specify viewport window (from 0,0 to 800,800)
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);

	//========================================================================//
	// DEFAULT OBJECT VAO
	//========================================================================//

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();

	//========================================================================//
	// LIGHT VAO
	//========================================================================//

	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	
	glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos(1.3f);

	// texture
	Texture si_fi("si-fi.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	si_fi.texUnit(shaderProgram, "tex0", 0);

	//========================================================================//
	// CAMERA
	//========================================================================//

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 12.0f));

	//========================================================================//
	// WINDOW
	//========================================================================//

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.UpdateMatrix(45.0f, 0.01f, 100.0f);
		camera.Inputs(window);

		//========================================================================//
		// OBJECT
		//========================================================================//

		shaderProgram.Activate();

		// adjusting model behavior
		float angle = (float)glfwGetTime() * glm::radians(50.0f);

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(1.2f));
		model = glm::translate(model, glm::vec3(0.0f));
		model = glm::rotate(model, angle, glm::vec3(0.1f, 0.2f, 0.0f)); 
		// -> where x, y, z is axis of rotation (e.g. 0 1 0)

		camera.Matrix(shaderProgram, "camMatrix");
		
		///////////////////////////////////////////////////////////
		// Linking uniform for each mat4
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		///////////////////////////////////////////////////////////
		si_fi.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		
		//========================================================================//
		// LIGHT
		//========================================================================//
		
		lightShader.Activate();

		glm::mat4 lightObject(1.0f);
		lightObject = glm::translate(lightObject, lightPos);
		lightObject = glm::scale(lightObject, glm::vec3(1.3f));

		camera.Matrix(lightShader, "camMatrix");
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightObject));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();  //All "poll" events with window (such as window resizing and etc.)
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	si_fi.Delete();
	shaderProgram.Delete();
	//closing window and deleting
	glfwDestroyWindow(window);
	glfwTerminate();
}