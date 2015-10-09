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

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader1("./res/basicShader");
	Shader shader2("./res/basicShader");
	Shader shader3("./res/basicShader");

	Texture texture1("./res/bricksBad.jpg");
	Texture texture2("./res/bricks.jpg");
	Texture texture3("./res/bricks.jpg");

	Transform transform1;
	Transform transform2;
	Transform transform3;
	float counter = 0.0f;

	Entity entity1(mesh, shader1, texture1, transform1);
	Entity entity2(mesh, shader2, texture2, transform2);
	Entity entity3(mesh, shader3, texture1, transform3);

	/* ----- Setup window ----- */

	//Tell OpenGL the size of the rendering window
	//Making this smaller than the window size allows other elements to be displayed outside the OpenGL viewport
	glViewport(0, 0, WIDTH, HEIGHT);

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
		entity1.getTransform()->setPosX(cosf(counter) / 2);

		entity2.getTransform()->setPosY(cosf(counter) / 2);

		entity3.getTransform()->setPosX(sinf(counter) / 2);

		//Draw
		entity1.render(0);
		entity2.render(0);
		if (doTry)
		{
			entity3.render(0);
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