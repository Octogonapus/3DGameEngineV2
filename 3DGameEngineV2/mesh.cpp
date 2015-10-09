#include "mesh.h"
#include <vector>


Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	initMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].getPos());
		model.texCoords.push_back(*vertices[i].getTexCoord());
		model.normals.push_back(*vertices[i].getNormal());
	}

	for(unsigned int i = 0; i< numIndices; i++)
		model.indices.push_back(indices[i]);

	initMesh(model);

	//m_drawCount = numIndices;

	////Generate vao
	//glGenVertexArrays(1, &m_vao);
	//glBindVertexArray(m_vao);

	////Position and texture coordinate data
	//std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> texCoords;
	//positions.reserve(numVertices);
	//texCoords.reserve(numVertices);

	//for (unsigned int i = 0; i < numVertices; i++)
	//{
	//	positions.push_back(*vertices[i].getPos());
	//	texCoords.push_back(*vertices[i].getTexCoord());
	//}

	////Generate vertex array buffer array
	//glGenBuffers(NUM_BUFFERS, m_vab);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	////Generate texture coordindate buffer
	//glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	////Generate element array buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[INDEX_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	////Keep the vertex array from being edited outside this function
	//glBindVertexArray(0);
}

Mesh::~Mesh()
{
	//Delete vao
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::draw()
{
	glBindVertexArray(m_vao);

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::initMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();

	//Generate vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//Generate vertex array buffer array
	glGenBuffers(NUM_BUFFERS, m_vab);
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Generate texture coordindate buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Generate normal buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Generate element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	//Keep the vertex array from being edited outside this function
	glBindVertexArray(0);
}