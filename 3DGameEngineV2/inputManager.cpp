#include "inputManager.h"

//Global static pointer to ensure single instance
InputManager* InputManager::m_instance = nullptr;

//Singleton class - Return the same instance of this class
InputManager* InputManager::instance()
{
	if (!m_instance)
	{
		m_instance = new InputManager;

		//Make sure all keys are initialized to false
		for (unsigned int i = 0; i < 1024; i++)
			m_instance->m_keys[i] = false;
	}

	return m_instance;
}