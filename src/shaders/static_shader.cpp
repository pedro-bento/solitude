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
	location_shineDamper = Shader::getUniformLocation("shineDamper");
	location_reflectivity = Shader::getUniformLocation("reflectivity");
	location_useFakeLighting = Shader::getUniformLocation("useFakeLighting");
	location_skyColour = Shader::getUniformLocation("skyColour");
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

void StaticShader::loadViewMatrix(FPPCamera* camera)
{
	Shader::loadMatrix(location_viewMatrix, createViewMatrix(camera));
}

void StaticShader::loadLight(Light* light)
{
 	Shader::loadVector(location_lightPosition, light->getPosition());
	Shader::loadVector(location_lightColour, light->getColour());
}

void StaticShader::loadShineVariables(float damper, float reflectivity)
{
	Shader::loadFloat(location_shineDamper, damper);
	Shader::loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadFakeLightingVariable(bool useFake)
{
	Shader::loadBoolean(location_useFakeLighting, useFake);
}

void StaticShader::loadSkyColour(vec3 colour)
{
	Shader::loadVector(location_skyColour, colour);
}
