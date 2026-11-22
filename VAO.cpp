#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);      // ->
	// -> (vertex shader index, data size (3 for vertex - x,y,z), type, normallize (for GL_INT), stride between data for each verteces, pointer to the beggining of the data in the array)

	// 0 - index in vertex attribute - layout (location = x) in SORCE vertex 
	glEnableVertexAttribArray(layout); // index in array
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}