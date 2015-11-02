#include <fstream>
#include <iostream>
#include "shader.h"

static std::string loadShader(const std::string& fileName);
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint createShader(const std::string& code, GLenum type);

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	
	m_shaders[0] = createShader(loadShader("./res/shaders/" + fileName + ".vs"), GL_VERTEX_SHADER);	//Vertex shader
	m_shaders[1] = createShader(loadShader("./res/shaders/" + fileName + ".fs"), GL_FRAGMENT_SHADER);	//Fragment shader

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoords");
	glBindAttribLocation(m_program, 2, "normal");
	glBindAttribLocation(m_program, 3, "tangent");

	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Shader program link failed: ");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Shader program validation failed: ");

	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "view");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projection");
	
	m_uniforms[VIEWPOS_U] = glGetUniformLocation(m_program, "viewPos");
	m_uniforms[LIGHTPOS_U] = glGetUniformLocation(m_program, "lightPos");

	m_uniforms[MAT_DIFFUSE_U] = glGetUniformLocation(m_program, "diffuseMap");
	//m_uniforms[MAT_SPECULAR_U] = glGetUniformLocation(m_program, "material.specular");
	//m_uniforms[MAT_EMISSION_U] = glGetUniformLocation(m_program, "material.emission");
	m_uniforms[MAT_NORMAL_U] = glGetUniformLocation(m_program, "normalMap");
	/*m_uniforms[MAT_SHININESS_U] = glGetUniformLocation(m_program, "material.shininess");

	m_uniforms[DLIGHT_DIRECTION_U] = glGetUniformLocation(m_program, "dirLight.direction");
	m_uniforms[DLIGHT_AMBIENT_U] = glGetUniformLocation(m_program, "dirLight.ambient");
	m_uniforms[DLIGHT_DIFFUSE_U] = glGetUniformLocation(m_program, "dirLight.diffuse");
	m_uniforms[DLIGHT_SPECULAR_U] = glGetUniformLocation(m_program, "dirLight.specular");

	m_uniforms[PLIGHT_POSITION_U] = glGetUniformLocation(m_program, "pointLight.position");
	m_uniforms[PLIGHT_AMBIENT_U] = glGetUniformLocation(m_program, "pointLight.ambient");
	m_uniforms[PLIGHT_DIFFUSE_U] = glGetUniformLocation(m_program, "pointLight.diffuse");
	m_uniforms[PLIGHT_SPECULAR_U] = glGetUniformLocation(m_program, "pointLight.specular");
	m_uniforms[PLIGHT_CONSTANT_U] = glGetUniformLocation(m_program, "pointLight.constant");
	m_uniforms[PLIGHT_LINEAR_U] = glGetUniformLocation(m_program, "pointLight.position");
	m_uniforms[PLIGHT_QUADRATIC_U] = glGetUniformLocation(m_program, "pointLight.quadratic");*/
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

void Shader::update(const Transform& transform, const Camera& camera, const glm::vec3& lightPos)
{
	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &transform.getModel()[0][0]);
	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, &camera.getView()[0][0]);
	glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, &camera.getProjection()[0][0]);

	glUniform3f(m_uniforms[VIEWPOS_U], camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	glUniform3f(m_uniforms[LIGHTPOS_U], lightPos.x, lightPos.y, lightPos.z);

	glUniform1i(m_uniforms[MAT_DIFFUSE_U], 0);
	//glUniform1i(m_uniforms[MAT_SPECULAR_U], 3);
	//glUniform1i(m_uniforms[MAT_EMISSION_U], 2);
	glUniform1i(m_uniforms[MAT_NORMAL_U], 1);
	glUniform1i(glGetUniformLocation(m_program, "normalMapping"), 1);
	/*glUniform1f(m_uniforms[MAT_SHININESS_U], 32.0f);

	glUniform3f(m_uniforms[DLIGHT_DIRECTION_U], -0.2f, -1.0f, -0.3f);
	glUniform3f(m_uniforms[DLIGHT_AMBIENT_U], 0.05f, 0.05f, 0.05f);
	glUniform3f(m_uniforms[DLIGHT_DIFFUSE_U], 0.4f, 0.4f, 0.4f);
	glUniform3f(m_uniforms[DLIGHT_SPECULAR_U], 0.5f, 0.5f, 0.5f);

	glUniform3f(m_uniforms[PLIGHT_POSITION_U], 0.7f, 0.2f, 2.0f);
	glUniform3f(m_uniforms[PLIGHT_AMBIENT_U], 0.05f, 0.05f, 0.05f);
	glUniform3f(m_uniforms[PLIGHT_DIFFUSE_U], 0.8f, 0.8f, 0.8f);
	glUniform3f(m_uniforms[PLIGHT_SPECULAR_U], 1.0f, 1.0f, 1.0f);
	glUniform1f(m_uniforms[PLIGHT_CONSTANT_U], 1.0f);
	glUniform1f(m_uniforms[PLIGHT_LINEAR_U], 0.09f);
	glUniform1f(m_uniforms[PLIGHT_QUADRATIC_U], 0.032f);*/
}

static std::string loadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output, line;

	if (file.is_open())
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	else
		std::cerr << "Unable to load shader: " << fileName << std::endl;

	return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed: ");

	return shader;
}