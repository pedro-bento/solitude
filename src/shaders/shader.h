#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include "../utilities/load.h"

class Shader
{
	GLuint programID;

public:
	Shader() {}
	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	~Shader();

	void start();
	void stop();

protected:
	virtual void getAllUniformLocations() {}
	GLuint getUniformLocation(const GLchar* uniformName);

	virtual void bindAttributes() {}
	void bindAttribute(GLuint attribute, const GLchar *variableName);

	void loadFloat(GLuint location, GLfloat value);
	void loadInt(GLuint location, GLint value);
	void loadBoolean(GLuint location, bool value);
	void loadVector(GLuint location, vec3 vector);
	void loadMatrix(GLuint location, mat4 matrix);
	void load2DVector(GLuint location, vec2 vector);
};

#endif // SHADER_H
