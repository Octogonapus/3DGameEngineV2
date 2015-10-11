#include "entity.h"

Entity::~Entity()
{
	m_mesh.~Mesh();
	m_shader.~Shader();
	m_texture.~Texture();
}

void Entity::render(const Camera& camera, const glm::vec3& lightDir)
{
	m_texture.bind(0);
	m_shader.use();
	m_shader.update(m_transform, camera, lightDir);
	m_mesh.draw();
}