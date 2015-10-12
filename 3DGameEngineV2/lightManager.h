#ifndef LIGHTMANAGER_H_INCLUDED
#define LIGHTMANAGER_H_INCLUDED

#include <vector>
#include "directionalLight.h"
#include "pointLight.h"

class LightManager
{
public:
	//Singleton class
	static LightManager* instance();

	//Add a directional light
	inline void addDirectionalLight(const DirectionalLight& dLight) { m_directionalLights.push_back(dLight); }

	//Add a point light
	inline void addPointLight(const PointLight& pLight) { m_pointLights.push_back(pLight); }

	inline const DirectionalLight& getDirectionalLight(unsigned int index) const { return m_directionalLights[index]; }
	inline const std::vector<DirectionalLight>& getDirectionalLights() const { return m_directionalLights; }
	inline const PointLight& getPointLight(unsigned int index) const { return m_pointLights[index]; }
	inline const std::vector<PointLight>& getPointLights() const { return m_pointLights; }
private:
	//Singleton class
	LightManager(){};
	LightManager(LightManager const&){};
	LightManager& operator=(LightManager const&){};
	static LightManager* m_instance;

	//All directional lights
	std::vector<DirectionalLight> m_directionalLights;

	//All point lights
	std::vector<PointLight> m_pointLights;
};

#endif