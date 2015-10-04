#include <iostream>

//Include static GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//Include (default static) GLFW
#include <GLFW/glfw3.h>

#include "renderingEngine.h"

#define GLSL(src) "#version 150 core\n" #src

const GLuint WIDTH = 800, HEIGHT = 600;

//Function prototype - GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Main function - Entry point for the game engine
int main()
{
	RenderingEngine* re = RenderingEngine::instance();
	re->initialize(800, 600, "OpenGL", NULL, NULL);

	/* ----- Setup GL Buffers ----- */

	//Vertex array object
	GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	//Vertex buffer object
	GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	float vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Element buffer object
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	/* ----- Setup shaders ----- */

	//Create the vertex shader
    const char* vertexSource = GLSL(
        in vec2 position;
		in vec3 color;

		out vec3 Color;
        
        void main() {
			Color = color;
            gl_Position = vec4(position, 0.0, 1.0);
        }
    );

	//Setup and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	//Check if the vertex shader compiled correctly
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		std::cout << "Vertex shader compiled correctly." << std::endl;
	}
	else
	{
		std::cout << "Vertex shader compiled incorrectly." << std::endl;
	}

	//Create the fragment shader
    const char* fragmentSource = GLSL(
		in vec3 Color;

        out vec4 outColor;

        void main() {
            outColor = vec4(Color, 1.0);
        }
    );

	//Setup and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

	//Check if the fragment shader compiled correctly
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE)
	{
		std::cout << "Fragment shader compiled correctly." << std::endl;
	}
	else
	{
		std::cout << "Fragment shader compiled incorrectly." << std::endl;
	}

	//Combine shaders into a program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");

	//Link and use shader program
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//Specify vertex data input
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	//Specify color data input
	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw a triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	//Escape key should close the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}