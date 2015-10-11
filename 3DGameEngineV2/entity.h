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
	Entity(const Mesh& mesh, const std::string& shaderFileName, const std::string& textureFileName):
		m_mesh(mesh),
		m_shader(shaderFileName),
		m_texture(textureFileName),
		m_transform() {}
	Entity(const Mesh& mesh, const std::string& shaderFileName, const std::string& textureFileName, const std::string& specularMapTextureFileName):
		m_mesh(mesh),
		m_shader(shaderFileName),
		m_texture(textureFileName),
		m_hasSpecularMap(true),
		m_specularMapTexture(specularMapTextureFileName),
		m_transform() {}
	Entity(const Mesh& mesh, const std::string& shaderFileName, const std::string& textureFileName, const std::string& specularMapTextureFileName, const std::string& emissionMapTextureFileName):
		m_mesh(mesh),
		m_shader(shaderFileName),
		m_texture(textureFileName),
		m_hasSpecularMap(true),
		m_specularMapTexture(specularMapTextureFileName),
		m_hasEmissionMap(true),
		m_emissionMapTexture(emissionMapTextureFileName),
		m_transform() {}
	Entity(const Mesh& mesh, const Shader& shader, const Texture& texture, const Transform& transform):
		m_mesh(mesh),
		m_shader(m_shader),
		m_texture(texture),
		m_transform(transform) {}
	Entity(const Mesh& mesh, const Shader& shader, const Texture& texture, const Texture& specularMapTexture, const Transform& transform):
		m_mesh(mesh),
		m_shader(m_shader),
		m_texture(texture),
		m_hasSpecularMap(true),
		m_specularMapTexture(specularMapTexture),
		m_transform(transform) {}
	virtual ~Entity();

	//Render the entity
	void render(const Camera& camera, const glm::vec3& lightDir);

	inline Mesh* getMesh() { return &m_mesh; }
	inline Shader* getShader() { return &m_shader; }
	inline Texture* getTexture() { return &m_texture; }
	inline Transform* getTransform() { return &m_transform; }
private:
	//Mesh
	Mesh m_mesh;

	//Shader
	Shader m_shader;

	//Main texture (i.e. diffuse map)
	Texture m_texture;

	//Specular map
	bool m_hasSpecularMap = false;
	Texture m_specularMapTexture;

	//Emission map
	bool m_hasEmissionMap = false;
	Texture m_emissionMapTexture;

	//Transform
	Transform m_transform;
};

#endif