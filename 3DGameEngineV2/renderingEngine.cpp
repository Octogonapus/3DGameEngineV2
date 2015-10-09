#include "renderingEngine.h"
#include "shader.h"

//Global static pointer to ensure single instance
RenderingEngine* RenderingEngine::m_instance = NULL;

//Singleton class - Return the same instance of this class
RenderingEngine* RenderingEngine::instance()
{
	if (!m_instance)
		m_instance = new RenderingEngine;

	return m_instance;
}

//Initialize the rendering engine
void RenderingEngine::initialize(const GLuint width, const GLuint height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	/* ----- Start GLFW ----- */
	if (glfwInit() != GL_TRUE)
	{
		std::cout << "GLFW failed to initialize." << std::endl;
		std::cout << "RenderingEngine failed to initialize." << std::endl;
		return;
	}
	else
		std::cout << "GLFW initialized correctly." << std::endl;

	//Setup GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Make the window
	m_window = glfwCreateWindow(width, height, title, monitor, share);

	//Window must have been created correctly, so make the current context the new window
	glfwMakeContextCurrent(m_window);

	//Null pointer for window means the window didn't create correctly
	if (m_window == nullptr)
	{
		//Tell the user
		std::cout << "Failed to create GLFW window." << std::endl;
		std::cout << "RenderingEngine failed to initialize." << std::endl;

		//Shut down GLFW
		glfwTerminate();

		return;
	}
	else
		std::cout << "GLFW window created successfully." << std::endl;

	/* ----- Start GLEW ----- */

	//Use modern techniques to manage OpenGL functionality
	//Setting this to GL_FALSE could cause issues when using OpenGL core profile
	glewExperimental = GL_TRUE;

	//If GLEW failed to start correctly
	if (glewInit() != GLEW_OK)
	{
		//Tell the user
		std::cout << "GLEW failed to initialize." << std::endl;
		std::cout << "RenderingEngine failed to initialize." << std::endl;

		return;
	}
	else
		std::cout << "GLEW initialized correctly." << std::endl;

	//Tell OpenGL the size of the rendering window
	//Making this smaller than the window size allows other elements to be displayed outside the OpenGL viewport
	glViewport(0, 0, width, height);

	//Depth buffer
	glEnable(GL_DEPTH_TEST);

	//Back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	std::cout << "RenderingEngine initialized correctly." << std::endl;
}