#version 330 core

out vec4 fragment;

// inputs from vertex shader
in vec3 color;
in vec2 texCoords;
in vec3 normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform vec3 camPos;

void main()
{
    // constants
    float ambient = 0.2f;
    float specularLight = 0.5f;

    // diffuse part
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPos - currentPos);

    float diffuse = max(dot(norm, lightDirection), 0.0f);

    // specular part
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, norm);

    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specularLight * specularAmount;

    // final output
    fragment = texture(tex0, texCoords) * lightColor * (diffuse + ambient + specular);
}