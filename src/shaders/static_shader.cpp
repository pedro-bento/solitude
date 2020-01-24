#include "static_shader.h"

StaticShader::StaticShader()
	: Shader("./glsl/vertexShader.glsl",
					 "./glsl/fragmentShader.glsl")
{
	getAllUniformLocations();
}

StaticShader::~StaticShader()
{
}

void StaticShader::getAllUniformLocations()
{
	location_transformationMatrix = Shader::getUniformLocation("transformationMatrix");
	location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
	location_viewMatrix = Shader::getUniformLocation("viewMatrix");
}

void StaticShader::bindAttributes()
{
	Shader::bindAttribute(0, "position");
	Shader::bindAttribute(1, "textureCoords");
}

void StaticShader::loadTransformationMatrix(mat4 matrix)
{
	Shader::loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(mat4 matrix)
{
	Shader::loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera* camera)
{
	Shader::loadMatrix(location_viewMatrix, createViewMatrix(camera));
}
