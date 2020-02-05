#ifndef TERRAIN_SHADER
#define TERRAIN_SHADER

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

class TerrainShader : public Shader
{
  const int MAX_LIGHTS = 4;

  GLuint location_transformationMatrix;
  GLuint location_projectionMatrix;
  GLuint location_viewMatrix;
  vector<GLuint> location_lightPosition;
  vector<GLuint> location_lightColour;
  GLuint location_shineDamper;
  GLuint location_reflectivity;
  GLuint location_skyColour;
  GLuint location_backgroundTexture;
  GLuint location_rTexture;
  GLuint location_gTexture;
  GLuint location_bTexture;
  GLuint location_blendMap;

public:
  TerrainShader();
  ~TerrainShader();

  void getAllUniformLocations() override;
  void bindAttributes() override;

  void connectTextureUnits();
  void loadTransformationMatrix(mat4 matrix);
  void loadProjectionMatrix(mat4 matrix);
  void loadViewMatrix(FPPCamera* camera);
  void loadLights(vector<Light*> lights);
  void loadShineVariables(float damper, float reflectivity);
  void loadSkyColour(vec3 colour);
};

#endif
