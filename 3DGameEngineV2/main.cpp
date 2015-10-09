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

const GLuint WIDTH = 800, HEIGHT = 600;

//Function prototype - GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int button, int action, int mode);

//Temporary
bool doTry = false;

//Main function - Entry point for the game engine
int main()
{
	//Get an instance of and initialize the rendering engine
	RenderingEngine* re = RenderingEngine::instance();
	re->initialize(800, 600, "OpenGL", NULL, NULL);

	//Bind the callback functions
	glfwSetKeyCallback(re->getWindow(), key_callback);
	glfwSetMouseButtonCallback(re->getWindow(), mouse_callback);

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0))
	};

	unsigned int indices[] {0, 1, 2};

	Mesh mesh1("./res/monkey3.obj");

	Entity entity1(mesh1, "./res/basicShader", "./res/bricks.jpg");
	Entity entity2(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), "./res/basicShader", "./res/bricks.jpg");
	Entity entity3(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), "./res/basicShader", "./res/bricks.jpg");
	float counter = 0.0f;

	Camera camera(glm::vec3(0, 0, -5), 70.0f, 800.0f / 600.0f, 0.01f, 1000.0f);

	//Main game loop
	//Do not end the loop until the window has been told to close
	while (!glfwWindowShouldClose(re->getWindow()))
	{
		//Check if any events have been triggered and call their corresponding functions
		glfwPollEvents();

		//Clear the screen before each new render
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Update transforms
		entity1.getTransform()->setPosZ(sinf(counter) * 2);
		entity1.getTransform()->setRotY(counter / 2);

		entity2.getTransform()->setPosY(cosf(counter) / 2);
		entity2.getTransform()->setPosZ(1);

		entity3.getTransform()->setPosX(sinf(counter) / 2);

		//Draw
		entity1.render(camera);
		//entity2.render(camera);
		if (doTry)
		{
			entity3.render(camera);
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