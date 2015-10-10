#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <string>
#include <map>
#include "vertex.h"
#include "indexedModel.h"
#include "meshData.h"

class Mesh
{
public:
	Mesh(const std::string& fileName = "cube.obj");
	Mesh(const std::string& meshname, const IndexedModel& model);
	Mesh(const Mesh& mesh);
	//Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	virtual ~Mesh();

	//Render the mesh
	void draw() const;
private:
	static std::map<std::string, MeshData*> s_resourceMap;

	std::string m_fileName;
	MeshData* m_meshData;

	void operator=(Mesh& other){}
};

#endif