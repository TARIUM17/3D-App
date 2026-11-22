#include "Camera.h"

Camera::Camera(unsigned int width, unsigned int height, glm::vec3 Position)
	:width(width), height(height), Position(Position) {
	Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::vec3(1.0f, 0.0f, 0.0f);
	speed = 0.001f;
	sensitivity = 100.0f;
	cameraMatrix = glm::mat4(1.0f);
}

glm::vec3 Camera::getPosition() {
	return this->Position;
}

void Camera::UpdateMatrix(float FOV, float near, float far) {
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOV), (float)width / float(height), near, far);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	//
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -Right;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * Right;
	}
}