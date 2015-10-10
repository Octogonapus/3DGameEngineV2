#include "indexedModel.h"

bool IndexedModel::isValid() const
{
	return m_positions.size() == m_texCoords.size()
		&& m_texCoords.size() == m_normals.size()
		&& m_normals.size() == m_tangents.size();
}

IndexedModel IndexedModel::finalize()
{
	if (isValid())
		return *this;

	if (m_texCoords.size() == 0)
		for (unsigned int i = m_texCoords.size(); i < m_positions.size(); i++)
			m_texCoords.push_back(glm::vec2(0.0f, 0.0f));

	if (m_normals.size() == 0)
		calcNormals();

	if (m_tangents.size() == 0)
		calcTangents();

	return *this;
}

void IndexedModel::calcNormals()
{
	m_normals.clear();
	m_normals.reserve(m_positions.size());
	
	for(unsigned int i = 0; i < m_positions.size(); i++)
		m_normals.push_back(glm::vec3(0, 0, 0));

	for(unsigned int i = 0; i < m_indices.size(); i += 3)
	{
		int i0 = m_indices[i];
		int i1 = m_indices[i + 1];
		int i2 = m_indices[i + 2];
			
		glm::vec3 v1 = m_positions[i1] - m_positions[i0];
		glm::vec3 v2 = m_positions[i2] - m_positions[i0];
		
		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
		
		m_normals[i0] = m_normals[i0] + normal;
		m_normals[i1] = m_normals[i1] + normal;
		m_normals[i2] = m_normals[i2] + normal;
	}
	
	for(unsigned int i = 0; i < m_normals.size(); i++)
		m_normals[i] = glm::normalize(m_normals[i]);
}

void IndexedModel::calcTangents()
{
	m_tangents.clear();
	m_tangents.reserve(m_positions.size());
	
	for(unsigned int i = 0; i < m_positions.size(); i++)
		m_tangents.push_back(glm::vec3(0,0,0));
		
	for(unsigned int i = 0; i < m_indices.size(); i += 3)
    {
		int i0 = m_indices[i];
		int i1 = m_indices[i + 1];
		int i2 = m_indices[i + 2];
    
        glm::vec3 edge1 = m_positions[i1] - m_positions[i0];
        glm::vec3 edge2 = m_positions[i2] - m_positions[i0];
        
        float deltaU1 = m_texCoords[i1].x - m_texCoords[i0].x;
        float deltaU2 = m_texCoords[i2].x - m_texCoords[i0].x;
        float deltaV1 = m_texCoords[i1].y - m_texCoords[i0].y;
        float deltaV2 = m_texCoords[i2].y - m_texCoords[i0].y;
        
        float dividend = (deltaU1 * deltaV2 - deltaU2 * deltaV1);
        float f = dividend == 0.0f ? 0.0f : 1.0f/dividend;
        
        glm::vec3 tangent = glm::vec3(
			f * (deltaV2 * edge1.x - deltaV1 * edge2.x),
			f * (deltaV2 * edge1.y - deltaV1 * edge2.y),
			f * (deltaV2 * edge1.z - deltaV1 * edge2.z));

		m_tangents[i0] += tangent;
		m_tangents[i1] += tangent;
		m_tangents[i2] += tangent;	
    }

    for(unsigned int i = 0; i < m_tangents.size(); i++)
		m_tangents[i] = glm::normalize(m_tangents[i]);
}