#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

#endif