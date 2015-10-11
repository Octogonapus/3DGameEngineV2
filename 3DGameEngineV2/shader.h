#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader(){}
	Shader(const std::string& fileName);
	virtual ~Shader();

	//Bind this shader for use
	void use();

	//Update all the uniforms
	void update(const Transform& transform, const Camera& camera, const glm::vec3& lightPos);
private:
	//Full shader program
	GLuint m_program;

	//All individual shaders
	static const unsigned int NUM_SHADERS = 2;
	GLuint m_shaders[NUM_SHADERS];

	//Uniform enum
	enum
	{
		MODEL_U,
		VIEW_U,
		PROJECTION_U,
		VIEWPOS_U,
		MAT_DIFFUSE_U,
		MAT_SPECULAR_U,
		MAT_EMISSION_U,
		MAT_SHININESS_U,
		LIGHT_POSITION_U,
		LIGHT_AMBIENT_U,
		LIGHT_DIFFUSE_U,
		LIGHT_SPECULAR_U,
		NUM_UNIFORMS
	};

	//All uniforms
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif