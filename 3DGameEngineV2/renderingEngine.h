#ifndef RENDERINGENGINE_H_INCLUDED
#define RENDERINGENGINE_H_INCLUDED

//OpenGL includes
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//System includes
#include <iostream>

//RenderingEngine should handle all rendering related information and processes
class RenderingEngine
{
public:
	//Singleton class
	static RenderingEngine* instance();

	//Render a new image and refresh the window
	void render();

	//Initialize the rendering engine
	void initialize(const GLuint width, const GLuint height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);

	inline GLFWwindow* getWindow() { return m_window; }
private:
	//Singleton class
	RenderingEngine(){};
	RenderingEngine(RenderingEngine const&){};
	RenderingEngine& operator=(RenderingEngine const&){};
	static RenderingEngine* m_instance;

	//GLFWwindow reference
	GLFWwindow* m_window;
};

#endif