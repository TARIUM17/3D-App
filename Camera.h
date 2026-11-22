#pragma once
#include "BasicLibs.h"
#include "ShaderClass.h"

class Camera
{
private:
	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::mat4 cameraMatrix;

	unsigned int height, width;
	float speed, sensitivity;

public:
	Camera(unsigned int width, unsigned int height, glm::vec3 Position);
	glm::vec3 getPosition();
	void UpdateMatrix(float FOV, float near, float far);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
};

