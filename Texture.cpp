#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	type = texType;

	stbi_set_flip_vertically_on_load(true);
	int imgWidth, imgHeight, numChannels;
	unsigned char* bytes = stbi_load(image, &imgWidth, &imgHeight, &numChannels, 0);
	if (!bytes) {
		std::cout << "Failed to load texture image: " << image << "\n";
		return;
	}

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Format checker
	GLenum internalFormat = format;
	GLenum imageFormat = format;
	if (numChannels == 4) {
		internalFormat = GL_RGBA;
		imageFormat = GL_RGBA;
	}
	else if (numChannels == 3) {
		internalFormat = GL_RGB;
		imageFormat = GL_RGB;
	}
	else if (numChannels == 1) {
		internalFormat = GL_RED;
		imageFormat = GL_RED;
	}

	glTexImage2D(texType, 0, internalFormat, imgWidth, imgHeight, 0, imageFormat, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	shader.Activate();
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}