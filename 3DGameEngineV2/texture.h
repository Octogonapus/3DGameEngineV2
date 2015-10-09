#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>

class Texture
{
public:
	Texture(){}
	Texture(const std::string& fileName);
	virtual ~Texture();

	//Bind this texture for use
	void bind(unsigned int unit);

private:
	//Texture data
	GLuint m_texture;
};

#endif