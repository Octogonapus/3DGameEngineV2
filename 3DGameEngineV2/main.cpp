#include <iostream>

//Include static GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//Include (default static) GLFW
#include <GLFW/glfw3.h>

#include "renderingEngine.h"
#include "shader.h"
#include "vertex.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "entity.h"
#include "camera.h"
#include "inputManager.h"

const GLuint WIDTH = 800, HEIGHT = 600;

//GLFW callback functions
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int button, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//InputManager instance
InputManager* imInstance = InputManager::instance();

//Temporary
bool doTry = false;

//Main function - Entry point for the game engine
int main()
{
	//Get an instance of and initialize the rendering engine
	RenderingEngine* re = RenderingEngine::instance();
	re->initialize(800, 600, "OpenGL", NULL, NULL);

	//Register the callback functions
	glfwSetKeyCallback(re->getWindow(), key_callback);
	glfwSetMouseButtonCallback(re->getWindow(), mouse_callback);
	glfwSetCursorPosCallback(re->getWindow(), mouse_callback);
	glfwSetScrollCallback(re->getWindow(), scroll_callback);

	Vertex vertices[] = {
		Vertex{glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)},
		Vertex{glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)},
		Vertex{glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)}
	};

	unsigned int indices[] {0, 1, 2};

	Mesh mesh1("cubeNew.dae");

	Entity entity1(mesh1, "basicShader", "bricks.jpg");
	//Entity entity2(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), "./res/basicShader", "./res/bricks.jpg");
	//Entity entity3(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), "./res/basicShader", "./res/bricks.jpg");
	float counter = 0.0f;

	Camera mainCamera(glm::vec3(0, 0, 0), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	//Main game loop
	//Do not end the loop until the window has been told to close
	while (!glfwWindowShouldClose(re->getWindow()))
	{
		//Check if any events have been triggered and call their corresponding functions
		glfwPollEvents();

		//Clear the screen before each new render
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Update camera position
		glfwPollEvents();
		mainCamera.updateMovement();

		//Update transforms
		entity1.getTransform()->setRotX(counter / 2);
		entity1.getTransform()->setRotY(counter / 2);

		//Draw
		entity1.render(mainCamera);
		//entity2.render(camera);
		if (doTry)
		{
			//entity3.render(camera);
		}
		
		//Increment counter for transform modification
		counter += 0.01f;

		//Swap the color buffers to display the newly rendered image
		glfwSwapBuffers(re->getWindow());
	}

	//Game loop has been terminated and window has been closed
	//Terminate GLFW
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//Escape key closes the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		imInstance->setKey(key, true);
	else if (action == GLFW_RELEASE)
		imInstance->setKey(key, false);
}

void mouse_callback(GLFWwindow* window, int button, int action, int mode)
{
	//Left mouse button spawns a new mesh
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		doTry = true;
		std::cout << "Done." << std::endl;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	imInstance->setMouseX(xpos);
	imInstance->setMouseY(ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	imInstance->setScrollX(xoffset);
	imInstance->setScrollY(yoffset);
}