#include "meshData.h"
#include <iostream>

MeshData::MeshData(const IndexedModel& model):
	ReferenceCounter(),
	m_drawCount(model.getIndices().size())
{
	if (!model.isValid())
	{
		std::cout << "Error: Invalid mesh." << std::endl;
		assert(0 != 0);
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(NUM_BUFFERS, m_vab);
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getPositions().size() * sizeof(model.getPositions()[0]), &model.getPositions()[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getTexCoords().size() * sizeof(model.getTexCoords()[0]), &model.getTexCoords()[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getNormals().size() * sizeof(model.getNormals()[0]), &model.getNormals()[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vab[TANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.getTangents().size() * sizeof(model.getTangents()[0]), &model.getTangents()[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.getIndices().size() * sizeof(model.getIndices()[0]), &model.getIndices()[0], GL_STATIC_DRAW);
}

MeshData::~MeshData()
{
	glDeleteBuffers(NUM_BUFFERS, m_vab);
	glDeleteVertexArrays(1, &m_vao);
}

void MeshData::draw() const
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
}