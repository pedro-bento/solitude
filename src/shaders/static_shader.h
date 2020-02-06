#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include "shader.h"
#include "../entities/fpp_camera.h"
#include "../entities/light.h"
#include "../utilities/maths.h"

#include <string>
#include <vector>
using namespace std;

class StaticShader : public Shader
{
	const int MAX_LIGHTS = 4;

	GLuint location_transformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_viewMatrix;
	vector<GLuint> location_lightPosition;
  vector<GLuint> location_lightColour;
	vector<GLuint> location_attenuation;
	GLuint location_shineDamper;
	GLuint location_reflectivity;
	GLuint location_useFakeLighting;
	GLuint location_skyColour;
	GLuint location_numberOfRows;
	GLuint location_offset;

public:
	StaticShader();
	~StaticShader();

	void getAllUniformLocations() override;
	void bindAttributes() override;

	void loadTransformationMatrix(mat4 matrix);
	void loadProjectionMatrix(mat4 matrix);
	void loadViewMatrix(FPPCamera* camera);
	void loadLights(vector<Light*> lights);
	void loadShineVariables(float damper, float reflectivity);
	void loadFakeLightingVariable(bool useFake);
	void loadSkyColour(vec3 colour);
	void loadNumberOfRows(int numberOfRows);
	void loadOffset(float x, float y);
};

#endif // STATIC_SHADER_H
