#version 330 core

// out colors in RGBA
out vec4 fragment;


// inputs from vertex shader
in vec3 color;
in vec2 texCoords;

uniform sampler2D tex0;

void main()
{
    fragment = texture(tex0, texCoords);
}