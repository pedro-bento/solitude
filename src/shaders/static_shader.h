#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include "shader.h"
#include "../entities/camera.h"
#include "../entities/light.h"
#include "../utilities/maths.h"

class StaticShader : public Shader
{
	GLuint location_transformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_viewMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColour;
	GLuint location_shineDamper;
	GLuint location_reflectivity;
	GLuint location_useFakeLighting;

public:
	StaticShader();
	~StaticShader();

	void getAllUniformLocations() override;
	void bindAttributes() override;

	void loadTransformationMatrix(mat4 matrix);
	void loadProjectionMatrix(mat4 matrix);
	void loadViewMatrix(Camera* camera);
	void loadLight(Light* light);
	void loadShineVariables(float damper, float reflectivity);
	void loadFakeLightingVariable(bool useFake);

};

#endif // STATIC_SHADER_H
