#ifndef POINTLIGHT_H_INCLUDED
#define POINTLIGHT_H_INCLUDED

#include <glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

class PointLight
{
public:
	PointLight(){}
	PointLight(const glm::vec3& position, const float constant, const float linear, const float quadratic, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular):
		m_position(position),
		m_constant(constant),
		m_linear(linear),
		m_quadratic(quadratic),
		m_ambient(ambient),
		m_diffuse(diffuse),
		m_specular(specular) {}

	//Uniform enum
	enum PointLightUniformType
	{
		PLIGHT_POSITION_U,
		PLIGHT_AMBIENT_U,
		PLIGHT_DIFFUSE_U,
		PLIGHT_SPECULAR_U,
		PLIGHT_CONSTANT_U,
		PLIGHT_LINEAR_U,
		PLIGHT_QUADRATIC_U,
		NUM_UNIFORMS
	};

	inline GLuint getUniform(PointLightUniformType type) const { return m_uniforms[type]; }
	inline glm::vec3 getPosition() const { return m_position; }
	inline float getAttenConstant() const { return m_constant; }
	inline float getAttenLinear() const { return m_linear; }
	inline float getAttenQuadratic() const { return m_quadratic; }
	inline glm::vec3 getAmbient() const { return m_ambient; }
	inline glm::vec3 getDiffuse() const { return m_diffuse; }
	inline glm::vec3 getSpecular() const { return m_specular; }

	inline void setUniform(PointLightUniformType type, GLuint value) { m_uniforms[type] = value; }
private:
	//Position
	glm::vec3 m_position;

	//Attenuation
	float m_constant, m_linear, m_quadratic;

	//Ambient light
	glm::vec3 m_ambient;

	//Diffuse light
	glm::vec3 m_diffuse;

	//Specular light
	glm::vec3 m_specular;

	//All uniforms
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif