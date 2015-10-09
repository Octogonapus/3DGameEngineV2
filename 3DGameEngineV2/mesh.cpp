#include "mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;
	//Generate vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//Position and texture coordinate data
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].getPos());
		texCoords.push_back(*vertices[i].getTexCoord());
	}

	//Generate vertex array buffer array
	glGenBuffers(NUM_BUFFERS, m_vab);
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Generate texture coordindate buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Keep the vertex array from being edited outside this function
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	//Delete vao
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::draw()
{
	glBindVertexArray(m_vao);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}