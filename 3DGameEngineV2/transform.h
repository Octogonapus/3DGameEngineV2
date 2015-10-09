#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include <glm.hpp>
#include <gtx/transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)):
		m_pos(pos),
		m_rot(rot),
		m_scale(scale) {}

	//Get the full model of this transform
	inline glm::mat4 getModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_pos);
		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& getPos() { return m_pos; }
	inline glm::vec3& getRot() { return m_rot; }
	inline glm::vec3& getScale() { return m_scale; }

	inline void setPos(glm::vec3& pos) { m_pos = pos; }
	inline void setPosX(const float val) { m_pos.x = val; }
	inline void setPosY(const float val) { m_pos.y = val; }
	inline void setPosZ(const float val) { m_pos.z = val; }

	inline void setRot(glm::vec3& rot) { m_rot = rot; }
	inline void setRotX(const float val) { m_rot.x = val; }
	inline void setRotY(const float val) { m_rot.y = val; }
	inline void setRotZ(const float val) { m_rot.z = val; }

	inline void setScale(glm::vec3& scale) { m_scale = scale; }
	inline void setScaleX(const float val) { m_scale.x = val; }
	inline void setScaleY(const float val) { m_scale.y = val; }
	inline void setScaleZ(const float val) { m_scale.z = val; }
private:
	//Position
	glm::vec3 m_pos;

	//Rotation
	glm::vec3 m_rot;

	//Scale
	glm::vec3 m_scale;
};

#endif