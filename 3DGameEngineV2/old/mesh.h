#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>
#include "vertex.h"
#include "obj_loader.h"

class Mesh
{
public:
	Mesh(){}
	Mesh(const std::string& fileName);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	virtual ~Mesh();

	//Render the mesh
	void draw();
private:
	//Vertex array object
	GLuint m_vao;

	//Vertex array buffer array
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,
		NUM_BUFFERS
	};

	GLuint m_vab[NUM_BUFFERS];

	//How much to draw
	unsigned int m_drawCount;

	void initMesh(const IndexedModel& model);
};

#endif