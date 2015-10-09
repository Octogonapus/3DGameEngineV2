#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"

class Entity
{
public:
	Entity(){}
	Entity(const Mesh& mesh, const Shader& shader, const Texture& texture, const Transform& transform):
		m_mesh(mesh),
		m_shader(shader),
		m_texture(texture),
		m_transform(transform) {}
	virtual ~Entity();

	//Render the entity
	void render(unsigned int textureUnit);

	inline Mesh* getMesh() { return &m_mesh; }
	inline Shader* getShader() { return &m_shader; }
	inline Texture* getTexture() { return &m_texture; }
	inline Transform* getTransform() { return &m_transform; }
private:
	Mesh m_mesh;
	Shader m_shader;
	Texture m_texture;
	Transform m_transform;
};

#endif