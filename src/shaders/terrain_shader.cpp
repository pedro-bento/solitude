#include "terrain_shader.h"

TerrainShader::TerrainShader()
	: Shader("./glsl/terrainVertexShader.glsl",
					 "./glsl/terrainFragmentShader.glsl")
{
	getAllUniformLocations();
}

TerrainShader::~TerrainShader()
{
}

void TerrainShader::getAllUniformLocations()
{
	location_transformationMatrix = Shader::getUniformLocation("transformationMatrix");
	location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
	location_viewMatrix = Shader::getUniformLocation("viewMatrix");
	location_lightPosition = Shader::getUniformLocation("lightPosition");
	location_lightColour = Shader::getUniformLocation("lightColour");
	location_shineDamper = Shader::getUniformLocation("shineDamper");
	location_reflectivity = Shader::getUniformLocation("reflectivity");
}

void TerrainShader::bindAttributes()
{
	Shader::bindAttribute(0, "position");
	Shader::bindAttribute(1, "textureCoords");
	Shader::bindAttribute(2, "normal");
}

void TerrainShader::loadTransformationMatrix(mat4 matrix)
{
	Shader::loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(mat4 matrix)
{
	Shader::loadMatrix(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(Camera* camera)
{
	Shader::loadMatrix(location_viewMatrix, createViewMatrix(camera));
}

void TerrainShader::loadLight(Light* light)
{
 	Shader::loadVector(location_lightPosition, light->getPosition());
	Shader::loadVector(location_lightColour, light->getColour());
}

void TerrainShader::loadShineVariables(float damper, float reflectivity)
{
	Shader::loadFloat(location_shineDamper, damper);
	Shader::loadFloat(location_reflectivity, reflectivity);
}
