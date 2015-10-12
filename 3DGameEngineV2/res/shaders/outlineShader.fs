#version 330 core

in vec2 texCoord0;
in vec3 normal0;

out vec4 color;

uniform sampler2D diffuse;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}