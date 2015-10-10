#ifndef INDEXEDMODEL_H_INCLUDED
#define INDEXEDMODEL_H_INCLUDED

#include <glm.hpp>
#include <string>
#include <vector>

class IndexedModel
{
public:
	IndexedModel(){}
	IndexedModel(const std::vector<unsigned int> indices, const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texCoords,
				 const std::vector<glm::vec3> normals = std::vector<glm::vec3>(), const std::vector<glm::vec3>& tangents = std::vector<glm::vec3>()):
				 m_indices(indices),
				 m_positions(positions),
				 m_texCoords(texCoords),
				 m_normals(normals),
				 m_tangents(tangents) {}

	bool isValid() const;
	void calcNormals();
	void calcTangents();

	IndexedModel finalize();

	inline const std::vector<unsigned int>& getIndices() const { return m_indices; }
	inline const std::vector<glm::vec3>& getPositions() const { return m_positions; }
	inline const std::vector<glm::vec2>& getTexCoords() const { return m_texCoords; }
	inline const std::vector<glm::vec3>& getNormals() const { return m_normals; }
	inline const std::vector<glm::vec3>& getTangents() const { return m_tangents; }
private:
	std::vector<unsigned int> m_indices;
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_tangents;
};

#endif