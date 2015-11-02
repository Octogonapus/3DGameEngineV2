#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 texCoord0;
out vec3 normal0;
out vec3 fragPos0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = mat3(transpose(inverse(model))) * normal;
	fragPos0 = vec3(model * vec4(position, 1.0f));
}