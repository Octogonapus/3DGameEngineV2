#include "entity.h"

Entity::~Entity()
{
	m_mesh.~Mesh();
	m_shader.~Shader();
	m_texture.~Texture();
}

void Entity::render(unsigned int textureUnit)
{
	m_texture.bind(textureUnit);
	m_shader.bind();
	m_shader.update(m_transform);
	m_mesh.draw();
}