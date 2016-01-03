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

//RenderingEngine instance
RenderingEngine* re = RenderingEngine::instance();

//InputManager instance
InputManager* imInstance = InputManager::instance();

//Main function - Entry point for the game engine
int main()
{
	//Initialize RenderingEngine instance
	re->initialize(800, 600, "OpenGL", NULL, NULL);

	//Register the callback functions
	glfwSetKeyCallback(re->getWindow(), key_callback);
	glfwSetMouseButtonCallback(re->getWindow(), mouse_callback);
	glfwSetCursorPosCallback(re->getWindow(), mouse_callback);
	glfwSetScrollCallback(re->getWindow(), scroll_callback);

	Mesh mesh1("cube.obj");

	Entity entity1(mesh1, "normalTest", "container2.png", "blank.png", "blank_normal.png", "blank.png");
	Entity entity1Outline(mesh1, "outlineShader", "bricks.jpg");
	entity1Outline.getTransform()->setScale(glm::vec3(1.1f, 1.1f, 1.1f));
	entity1.getTransform()->setPos(glm::vec3(0, -2, 0));

	//Entity entity2(mesh1, "basicShader", "container2.png", "container2_specular.png");
	//entity2.getTransform()->setPos(glm::vec3(-2, 0, -3));
	Entity entity2Outline(mesh1, "outlineShader", "bricks.jpg");
	entity2Outline.getTransform()->setPos(glm::vec3(-2, 0, -3));
	entity2Outline.getTransform()->setScale(glm::vec3(1.1f, 1.1f, 1.1f));

	Entity pointLight1(mesh1, "lampShader", "bricks.jpg");
	pointLight1.getTransform()->setPos(glm::vec3(0, -0.5f, 0));
	pointLight1.getTransform()->setScale(glm::vec3(0.05f, 0.05f, 0.05f));

	float counter = 0.0f;

	Camera mainCamera(glm::vec3(0, 0, 3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

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

		//Draw
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0x00);
		pointLight1.render(mainCamera, pointLight1.getTransform()->getPos());
		pointLight1.getTransform()->setPosX(1.5 * sinf(counter));
		pointLight1.getTransform()->setPosZ(1.5 * sinf(counter));

		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		entity1.render(mainCamera, pointLight1.getTransform()->getPos());
		//entity2.render(mainCamera, pointLight1.getTransform()->getPos());

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		//glDisable(GL_DEPTH_TEST);
		//entity1Outline.render(mainCamera, pointLight1.getTransform()->getPos());
		//entity2Outline.render(mainCamera);
		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);
		
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
	//Left mouse button changes cursor context
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		if (glfwGetInputMode(re->getWindow(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
			//Have GLFW capture the cursor
			glfwSetInputMode(re->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			//Have GLFW release the cursor
			glfwSetInputMode(re->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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