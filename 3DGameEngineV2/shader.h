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
	void update(const Transform& transform, const Camera& camera);
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
		DLIGHT_DIRECTION_U,
		DLIGHT_AMBIENT_U,
		DLIGHT_DIFFUSE_U,
		DLIGHT_SPECULAR_U,
		PLIGHT_POSITION_U,
		PLIGHT_AMBIENT_U,
		PLIGHT_DIFFUSE_U,
		PLIGHT_SPECULAR_U,
		PLIGHT_CONSTANT_U,
		PLIGHT_LINEAR_U,
		PLIGHT_QUADRATIC_U,
		NUM_UNIFORMS
	};

	//All uniforms
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif