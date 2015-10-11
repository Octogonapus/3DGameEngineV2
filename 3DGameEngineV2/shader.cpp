#include <fstream>
#include <iostream>
#include "shader.h"

static std::string loadShader(const std::string& fileName);
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage, const std::string& successMessage);
static GLuint createShader(const std::string& code, GLenum type);

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	
	m_shaders[0] = createShader(loadShader("./res/shaders/" + fileName + ".vs"), GL_VERTEX_SHADER);	//Vertex shader
	m_shaders[1] = createShader(loadShader("./res/shaders/" + fileName + ".fs"), GL_FRAGMENT_SHADER);	//Fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Shader program link failed: ", "Shader program link succeeded.");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Shader program validation failed: ", "Shader program validation succeeded.");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

void Shader::use()
{
	glUseProgram(m_program);
}

void Shader::update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.getViewProjection() * transform.getModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static std::string loadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output, line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}

		std::cout << "Shader loaded correctly." << std::endl;
	}
	else
		std::cerr << "Unable to load shader: " << fileName << std::endl;

	return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage, const std::string& successMessage)
{
	GLint success = 0;
	GLchar error[1024] = {0};

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << "; '" << error << "'" << std::endl;
	}
	else
	{
		std::cout << successMessage << std::endl;
	}
}

static GLuint createShader(const std::string& code, GLenum type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Shader creation failed." << std::endl;

	const GLchar* shaderSource[1];
	GLint shaderSourceLength[1];
	shaderSource[0] = code.c_str();
	shaderSourceLength[0] = code.length();

	glShaderSource(shader, 1, shaderSource, shaderSourceLength);
	glCompileShader(shader);
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed: ", "Shader compilation succeeded.");

	return shader;
}