#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 texCoord0;
in vec3 normal0;
in vec3 fragPos0;

out vec4 color;

uniform sampler2D diffuse;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	//color = texture(diffuse, texCoord0) * clamp(dot(-vec3(0, 0, 1), normal0), 0.0, 1.0);
	//color = vec4(lightColor * objectColor, 1.0f);

	//Ambient
	vec3 ambient = light.ambient * material.ambient;

	//Diffuse
	vec3 norm = normalize(normal0);
	vec3 lightDir = normalize(lightPos - fragPos0);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//Specular
	vec3 viewDir = normalize(viewPos - fragPos0);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular) * objectColor;
	color = vec4(result, 1.0f);
}