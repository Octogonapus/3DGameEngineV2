#include "mesh.h"
#include <vector>
#include <iostream>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

std::map<std::string, MeshData*> Mesh::s_resourceMap;

Mesh::Mesh(const std::string& meshName, const IndexedModel& model):
	m_fileName(meshName)
{
	std::map<std::string, MeshData*>::const_iterator it = s_resourceMap.find(meshName);

	if (it != s_resourceMap.end())
	{
		std::cout << "Error adding mesh " << meshName << ": A mesh by the same name already exists." << std::endl;
		assert(0 != 0);
	}
	else
	{
		m_meshData = new MeshData(model);
		s_resourceMap.insert(std::pair<std::string, MeshData*>(meshName, m_meshData));
	}
}

Mesh::Mesh(const std::string& fileName):
	m_fileName(fileName),
	m_meshData(0)
{
	std::map<std::string, MeshData*>::const_iterator it = s_resourceMap.find(fileName);
	if(it != s_resourceMap.end())
	{
		m_meshData = it->second;
		m_meshData->addReference();
	}
	else
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(("./res/models/" + fileName).c_str(),
												 aiProcess_Triangulate |
												 aiProcess_GenSmoothNormals |
												 aiProcess_FlipUVs |
												 aiProcess_CalcTangentSpace);

		if (!scene)
		{
			std::cout << "Mesh loading failed for mesh " << fileName << std::endl;
			assert(0 == 0);
		}

		const aiMesh* model = scene->mMeshes[0];

		std::vector<unsigned int> indices;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> tangents;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
		for (unsigned int i = 0; i < model->mNumVertices; i++)
		{
			const aiVector3D pos = model->mVertices[i];
			const aiVector3D texCoord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiZeroVector;
			const aiVector3D normal = model->mNormals[i];
			const aiVector3D tangent = model->mTangents[i];

			positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
			texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
			normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
			tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
		}

		for (unsigned int i = 0; i < model->mNumFaces; i++)
		{
			const aiFace& face = model->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		m_meshData = new MeshData(IndexedModel(indices, positions, texCoords, normals, tangents));
		s_resourceMap.insert(std::pair<std::string, MeshData*>(fileName, m_meshData));
	}
}

Mesh::Mesh(const Mesh& mesh):
	m_fileName(mesh.m_fileName),
	m_meshData(mesh.m_meshData)
{
	m_meshData->addReference();
}

Mesh::~Mesh()
{
	if (m_meshData && m_meshData->removeReference())
	{
		if (m_fileName.length() > 0)
			s_resourceMap.erase(m_fileName);

		delete m_meshData;
	}
}

void Mesh::draw() const
{
	m_meshData->draw();
}

//Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
//{
//	IndexedModel model;
//
//	for (unsigned int i = 0; i < numVertices; i++)
//	{
//		model.positions.push_back(*vertices[i].getPos());
//		model.getPositions().push_back(*vertices[i].pos);
//		model.texCoords.push_back(*vertices[i].getTexCoord());
//		model.normals.push_back(*vertices[i].getNormal());
//	}
//
//	for(unsigned int i = 0; i< numIndices; i++)
//		model.indices.push_back(indices[i]);
//
//	initMesh(model);
//
//	//m_drawCount = numIndices;
//
//	////Generate vao
//	//glGenVertexArrays(1, &m_vao);
//	//glBindVertexArray(m_vao);
//
//	////Position and texture coordinate data
//	//std::vector<glm::vec3> positions;
//	//std::vector<glm::vec2> texCoords;
//	//positions.reserve(numVertices);
//	//texCoords.reserve(numVertices);
//
//	//for (unsigned int i = 0; i < numVertices; i++)
//	//{
//	//	positions.push_back(*vertices[i].getPos());
//	//	texCoords.push_back(*vertices[i].getTexCoord());
//	//}
//
//	////Generate vertex array buffer array
//	//glGenBuffers(NUM_BUFFERS, m_vab);
//	//glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);
//	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
//
//	//glEnableVertexAttribArray(0);
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	////Generate texture coordindate buffer
//	//glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);
//	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
//
//	//glEnableVertexAttribArray(1);
//	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	////Generate element array buffer
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[INDEX_VB]);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
//
//	////Keep the vertex array from being edited outside this function
//	//glBindVertexArray(0);
//}
//
//Mesh::~Mesh()
//{
//	//Delete vao
//	glDeleteVertexArrays(1, &m_vao);
//}
//
//void Mesh::draw()
//{
//	glBindVertexArray(m_vao);
//
//	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
//	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
//
//	glBindVertexArray(0);
//}
//
//void Mesh::initMesh(const IndexedModel& model)
//{
//	m_drawCount = model.indices.size();
//
//	//Generate vao
//	glGenVertexArrays(1, &m_vao);
//	glBindVertexArray(m_vao);
//
//	//Generate vertex array buffer array
//	glGenBuffers(NUM_BUFFERS, m_vab);
//	glBindBuffer(GL_ARRAY_BUFFER, m_vab[POSITION_VB]);
//	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	//Generate texture coordindate buffer
//	glBindBuffer(GL_ARRAY_BUFFER, m_vab[TEXCOORD_VB]);
//	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	//Generate normal buffer
//	glBindBuffer(GL_ARRAY_BUFFER, m_vab[NORMAL_VB]);
//	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	//Generate element array buffer
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[INDEX_VB]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);
//
//	//Keep the vertex array from being edited outside this function
//	glBindVertexArray(0);
//}