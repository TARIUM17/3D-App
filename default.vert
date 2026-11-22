#version 330 core

//Positons
layout (location = 0) in vec3 aPos;
//Colors
layout (location = 1) in vec3 aColor;
//Texture coords
layout (location = 2) in vec2 aTex;
//Normal
layout (location = 3) in vec3 aNormal;

// output color, texture for the fragment shader
out vec3 color;
out vec2 texCoords;
out vec3 normal;
out vec3 currentPos;

uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
	// calculate light position based on world coordinates
	currentPos = vec3(model * vec4(aPos, 1.0f));

	color = aColor;
	texCoords = aTex;
	normal = mat3(model) * aNormal;
	
	gl_Position = camMatrix * vec4(currentPos, 1.0f);
}