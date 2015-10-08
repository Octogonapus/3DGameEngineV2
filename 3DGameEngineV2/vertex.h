#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <glm.hpp>

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->m_pos = pos;
		this->m_texCoord = texCoord;
	}

	inline glm::vec3* getPos() { return &m_pos; }
	inline glm::vec2* getTexCoord() { return &m_texCoord; }

private:
	//Vertex position data
	glm::vec3 m_pos;

	//Texture coordinate data
	glm::vec2 m_texCoord;
};

#endif