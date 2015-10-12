#ifndef DIRECTIONALLIGHT_H_INCLUDED
#define DIRECTIONALLIGHT_H_INCLUDED

#include <glm.hpp>

class DirectionalLight
{
public:
	DirectionalLight(){}
	DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular):
		m_direction(direction),
		m_ambient(ambient),
		m_diffuse(diffuse),
		m_specular(specular) {}

	inline glm::vec3 getDirection() const { return m_direction; }
	inline glm::vec3 getAmbient() const { return m_ambient; }
	inline glm::vec3 getDiffuse() const { return m_diffuse; }
	inline glm::vec3 getSpecular() const { return m_specular; }
private:
	//Direction
	glm::vec3 m_direction;

	//Ambient light
	glm::vec3 m_ambient;

	//Diffuse light
	glm::vec3 m_diffuse;

	//Specular light
	glm::vec3 m_specular;
};

#endif