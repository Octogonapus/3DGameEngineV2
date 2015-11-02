#include "entity.h"

Entity::~Entity()
{
	m_mesh.~Mesh();
	m_shader.~Shader();
	m_texture.~Texture();
}

void Entity::render(const Camera& camera, const glm::vec3& lightPos)
{
	m_texture.bind(0);

	if (m_hasSpecularMap)
		m_specularMapTexture.bind(3);
	
	if (m_hasEmissionMap)
		m_emissionMapTexture.bind(2);
	
	if (m_hasNormalMap)
		m_normalMapTexture.bind(1);

	m_shader.use();
	m_shader.update(m_transform, camera, lightPos);
	m_mesh.draw();
}