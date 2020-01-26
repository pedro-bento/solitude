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
	location_lightPosition = Shader::getUniformLocation("lightPosition");
	location_lightColour = Shader::getUniformLocation("lightColour");
}

void StaticShader::bindAttributes()
{
	Shader::bindAttribute(0, "position");
	Shader::bindAttribute(1, "textureCoords");
	Shader::bindAttribute(2, "normal");
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

void StaticShader::loadLight(Light* light)
{
 	Shader::loadVector(location_lightPosition, light->getPosition());
	Shader::loadVector(location_lightColour, light->getColour());
}
