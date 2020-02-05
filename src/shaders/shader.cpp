#include "shader.h"

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
	GLuint vertexShaderID = loadShader(vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = loadShader(fragmentFilePath, GL_FRAGMENT_SHADER);

	programID = glCreateProgram();

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

  bindAttributes();

	glLinkProgram(programID);

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	GLint result = GL_FALSE;
	int infoLogLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		vector<char> pogramErrorMessage((size_t)infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &pogramErrorMessage[0]);
		fprintf(stderr, "Failed to create shader program %s\n", &pogramErrorMessage[0]);
		cin.get();
		glDeleteProgram(programID);
		exit(EXIT_FAILURE);
	}

  getAllUniformLocations();
}

Shader::~Shader()
{
	stop();
	glDeleteProgram(programID);
}

void Shader::start()
{
	glUseProgram(programID);
}

void Shader::stop()
{
	glUseProgram(0);
}

GLuint Shader::getUniformLocation(const GLchar* uniformName)
{
	return glGetUniformLocation(programID, uniformName);
}

void Shader::bindAttribute(GLuint attribute, const GLchar* variableName)
{
	glBindAttribLocation(programID, attribute, variableName);
}

void Shader::loadFloat(GLuint location, GLfloat value)
{
	glUniform1f(location, value);
}

void Shader::loadInt(GLuint location, GLint value)
{
	glUniform1i(location, value);
}

void Shader::loadBoolean(GLuint location, bool value)
{
	if(value)
		loadFloat(location, 1.0f);
	else
		loadFloat(location, 0.0f);
}

void Shader::loadVector(GLuint location, vec3 vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::loadMatrix(GLuint location, mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::load2DVector(GLuint location, vec2 vector)
{
	glUniform2f(location, vector.x, vector.y);
}
