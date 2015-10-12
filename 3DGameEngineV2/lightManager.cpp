#include "lightManager.h"

//Global static pointer to ensure single instance
LightManager* LightManager::m_instance = nullptr;

//Singleton class - Return the same instance of this class
LightManager* LightManager::instance()
{
	if (!m_instance)
	{
		m_instance = new LightManager;
		m_instance->m_directionalLights.clear();
		m_instance->m_pointLights.clear();
	}

	return m_instance;
}