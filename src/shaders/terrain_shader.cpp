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
	location_skyColour = Shader::getUniformLocation("skyColour");
	location_backgroundTexture = Shader::getUniformLocation("backgroundTexture");
  location_rTexture = Shader::getUniformLocation("rTexture");
  location_gTexture = Shader::getUniformLocation("gTexture");
  location_bTexture = Shader::getUniformLocation("bTexture");
  location_blendMap = Shader::getUniformLocation("blendMap");
}

void TerrainShader::connectTextureUnits()
{
	Shader::loadInt(location_backgroundTexture, 0);
	Shader::loadInt(location_rTexture, 1);
	Shader::loadInt(location_gTexture, 2);
	Shader::loadInt(location_bTexture, 3);
	Shader::loadInt(location_blendMap, 4);
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

void TerrainShader::loadViewMatrix(FPPCamera* camera)
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

void TerrainShader::loadSkyColour(vec3 colour)
{
	Shader::loadVector(location_skyColour, colour);
}
