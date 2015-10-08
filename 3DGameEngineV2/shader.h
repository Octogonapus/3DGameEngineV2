#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	//Bind this shader for use
	void bind();
private:
	//Full shader program
	GLuint m_program;

	//All individual shaders
	static const unsigned int NUM_SHADERS = 2;
	GLuint m_shaders[NUM_SHADERS];

	////Shader program code
	//const char* m_vertexShaderCode = GLSL(
 //       in vec2 position;
	//	in vec3 color;

	//	out vec3 Color;
 //       
 //       void main() {
	//		Color = color;
 //           gl_Position = vec4(position, 0.0, 1.0);
 //       }
 //   );

	//const char* m_fragmentShaderCode = GLSL(
	//	in vec3 Color;

 //       out vec4 outColor;

 //       void main() {
 //           outColor = vec4(Color, 1.0);
 //       }
 //   );
};

#endif