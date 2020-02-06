#include "static_shader.h"

StaticShader::StaticShader()
: Shader("./glsl/vertexShader.glsl",
				 "./glsl/fragmentShader.glsl"),
  location_lightPosition(MAX_LIGHTS),
 	location_lightColour(MAX_LIGHTS),
	location_attenuation(MAX_LIGHTS)
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
	location_shineDamper = Shader::getUniformLocation("shineDamper");
	location_reflectivity = Shader::getUniformLocation("reflectivity");
	location_useFakeLighting = Shader::getUniformLocation("useFakeLighting");
	location_skyColour = Shader::getUniformLocation("skyColour");
	location_numberOfRows = Shader::getUniformLocation("numberOfRows");
	location_offset = Shader::getUniformLocation("offset");

	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		string lp = "lightPosition[" + to_string(i) + "]";
		location_lightPosition[i] = Shader::getUniformLocation(lp.c_str());
		string lc = "lightColour[" + to_string(i) + "]";
		location_lightColour[i] = Shader::getUniformLocation(lc.c_str());
		string a = "attenuation[" + to_string(i) + "]";
		location_attenuation[i] = Shader::getUniformLocation(a.c_str());
	}
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

void StaticShader::loadLights(vector<Light*> lights)
{
	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		if(i < lights.size())
		{
			Shader::loadVector(location_lightPosition[i], lights[i]->getPosition());
			Shader::loadVector(location_lightColour[i], lights[i]->getColour());
			Shader::loadVector(location_attenuation[i], lights[i]->getAttenuation());
		}
		else
		{
			Shader::loadVector(location_lightPosition[i], vec3(0.0f,0.0f,0.0f));
			Shader::loadVector(location_lightColour[i], vec3(0.0f,0.0f,0.0f));
			Shader::loadVector(location_attenuation[i], vec3(1.0f,0.0f,0.0f));
		}
	}
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

void StaticShader::loadNumberOfRows(int numberOfRows)
{
	Shader::loadFloat(location_numberOfRows, numberOfRows);
}

void StaticShader::loadOffset(float x, float y)
{
	Shader::load2DVector(location_offset, vec2(x,y));
}
