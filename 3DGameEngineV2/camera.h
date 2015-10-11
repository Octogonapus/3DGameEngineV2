#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

//Include (default static) GLFW
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx\transform.hpp>
#include <iostream>
#include "inputManager.h"

const GLfloat CAMERA_MOVEMENT_SPEED = 0.05f, CAMERA_MOUSE_SENSITIVITY = 0.05f;

class Camera
{
public:
	Camera(){}
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar):
		m_position(pos),
		m_fov(fov),
		m_aspect(aspect),
		m_zNear(zNear),
		m_zFar(zFar)
	{
		m_projection = glm::perspective(fov, aspect, zNear, zFar);
		m_forward = glm::vec3(0, 0, -1);
		m_up = glm::vec3(0, 1, 0);
	}

	//Camera view matrix
	inline glm::mat4 getView() const { return glm::lookAt(m_position, m_position + m_forward, m_up); }

	//Camera projection matrix
	inline glm::mat4 getProjection() const { return m_projection; }

	void updateMovement()
	{
		//W key moves the main camera foward
		if (imInstance->getKey(GLFW_KEY_W))
			m_position += CAMERA_MOVEMENT_SPEED * m_forward;

		//S key moves the main camera backward
		if (imInstance->getKey(GLFW_KEY_S))
			m_position -= CAMERA_MOVEMENT_SPEED * m_forward;

		//A key moves the main camera left
		if (imInstance->getKey(GLFW_KEY_A))
			m_position -= glm::normalize(glm::cross(m_forward, m_up)) * CAMERA_MOVEMENT_SPEED;

		//D key moves the main camera right
		if (imInstance->getKey(GLFW_KEY_D))
			m_position += glm::normalize(glm::cross(m_forward, m_up)) * CAMERA_MOVEMENT_SPEED;

		//Update rotation
		if (m_firstMouse)
		{
			m_lastX = imInstance->getMouseX();
			m_lastY = imInstance->getMouseY();
			m_firstMouse = false;
		}

		GLfloat xoffset = imInstance->getMouseX() - m_lastX;
		GLfloat yoffset = m_lastY - imInstance->getMouseY();
		m_lastX = imInstance->getMouseX();
		m_lastY = imInstance->getMouseY();

		xoffset *= CAMERA_MOUSE_SENSITIVITY;
		yoffset *= CAMERA_MOUSE_SENSITIVITY;

		m_yaw += xoffset;
		m_pitch += yoffset;

		//Bound rotation
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;

		if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		glm::vec3 tempFront;
		tempFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		tempFront.y = sin(glm::radians(m_pitch));
		tempFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_forward = glm::normalize(tempFront);
	}

	inline glm::vec3 getPosition() const { return m_position; }
	inline glm::vec3 getForward() const { return m_forward; }
	inline glm::vec3 getUp() const { return m_up; }

	inline void setPosition(const glm::vec3& newPos) { m_position = newPos; }
private:
	//View projection matrix
	glm::mat4 m_projection;

	//Camera position
	glm::vec3 m_position;

	//Camera rotation
	glm::vec3 m_forward, m_up;

	//First time doing mouse math
	bool m_firstMouse = true;

	//Previous cursor position
	GLfloat m_lastX = 800 / 2.0f, m_lastY = 600 / 2.0f;

	//Camera yaw and pitch
	GLfloat m_yaw = -90.0f, m_pitch = 0.0f;

	//Camera fov
	float m_fov;

	//Camera aspect ratio
	float m_aspect;
	
	//Camera near clipping plane
	float m_zNear;

	//Camera far clipping plane
	float m_zFar;

	//InputManager instance
	InputManager* imInstance = InputManager::instance();
};

#endif