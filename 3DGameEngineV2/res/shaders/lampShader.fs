#version 330 core

in vec2 texCoord0;
in vec3 normal0;

out vec4 color;

uniform sampler2D diffuse;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	//color = texture(diffuse, texCoord0) * clamp(dot(-vec3(0, 0, 1), normal0), 0.0, 1.0);
	color = vec4(1.0f);
}