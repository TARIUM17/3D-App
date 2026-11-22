#version 330 core

//Positons
layout (location = 0) in vec3 aPos;
//Colors
layout (location = 1) in vec3 aColor;
//Texture coords
layout (location = 2) in vec2 aTex;


// output color, texture for the fragment shader
out vec3 color;
out vec2 texCoords;

//uniform float scale;

//inputs matrix gor 3D
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0f);
	color = aColor;
	texCoords = aTex;
}