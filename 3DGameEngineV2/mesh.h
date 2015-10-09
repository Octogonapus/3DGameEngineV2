#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>
#include "vertex.h"

class Mesh
{
public:
	Mesh(){}
	Mesh(Vertex* vertices, unsigned int numVertices);
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
		NUM_BUFFERS
	};

	GLuint m_vab[NUM_BUFFERS];

	//How much to draw
	unsigned int m_drawCount;
};

#endif