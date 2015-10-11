#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
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

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	//Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord0));

	//Diffuse
	vec3 norm = normalize(normal0);
	vec3 lightDir = normalize(light.position - fragPos0);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord0));

	//Specular
	vec3 viewDir = normalize(viewPos - fragPos0);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord0));

	//Emission
	vec3 emission = vec3(texture(material.emission, texCoord0));

	//Output color
	color = vec4(ambient + diffuse + specular + emission, 1.0f);
}