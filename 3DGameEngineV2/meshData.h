#ifndef MESHDATA_H_INCLUDED
#define MESHDATA_H_INCLUDED

#include "referenceCounter.h"
#include "indexedModel.h"
//Include static GLEW
#define GLEW_STATIC
#include <GL/glew.h>

class MeshData : public ReferenceCounter
{
public:
	MeshData(const IndexedModel& model);
	virtual ~MeshData();

	//Render the mesh
	void draw() const;
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		TANGENT_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	//Vertex array object
	GLuint m_vao;

	//Vertex array buffer array
	GLuint m_vab[NUM_BUFFERS];

	//How much to draw
	int m_drawCount;

	MeshData(MeshData& other){}
	void operator=(MeshData& other){}
};

#endif