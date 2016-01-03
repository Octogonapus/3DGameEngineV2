#version 450 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	sampler2D normal;
	float shininess;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
};

in vec2 texCoord0;
in vec3 normal0;
in vec3 fragPos0;

out vec4 color;

#define NUM_DIRLIGHTS 1
#define NUM_POINTLIGHTS 1

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

void main()
{
	vec3 norm = texture(material.normal, texCoord0).rgb;
	norm = normalize(norm * 2.0 - 1.0);
	vec3 viewDir = normalize(viewPos - fragPos0);

	//Light sum
	vec3 result;

	//Directional light
	for (int i = 0; i < NUM_DIRLIGHTS; i++)
		result += calcDirLight(dirLight, norm, viewDir);

	//Point light
	for (int i = 0; i < NUM_POINTLIGHTS; i++)
		result += calcPointLight(pointLight, norm, viewDir, fragPos0);
	
	//Emission
	result += vec3(texture(material.emission, texCoord0));

	//Gamma correction
	result.rgb = pow(result.rgb, vec3(1.0 / 0.4)); //Gamma = 0.4

	color = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord0));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord0));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord0));

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord0));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord0));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord0));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}