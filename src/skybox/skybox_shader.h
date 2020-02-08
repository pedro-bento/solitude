#ifndef SKYBOX_SHADER_H
#define SKYBOX_SHADER_H

#include <glm/glm.hpp>
using namespace glm;

#include "../shaders/shader.h"
#include "../entities/fpp_camera.h"
#include "../utilities/maths.h"

class SkyboxShader : public Shader
{
  int location_projectionMatrix;
  int location_viewMatrix;

public:
  SkyboxShader()
  : Shader("./glsl/skyboxVertexShader.glsl",
           "./glsl/skyboxFragmentShader.glsl")
  {
    getAllUniformLocations();
  }

  void loadProjectionMatrix(mat4 matrix)
  {
    Shader::loadMatrix(location_projectionMatrix, matrix);
  }

  void loadViewMatrix(FPPCamera* camera)
  {
    mat4 matrix = createViewMatrix(camera);
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    Shader::loadMatrix(location_viewMatrix, matrix);
  }

  void getAllUniformLocations() override
  {
    location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
    location_viewMatrix = Shader::getUniformLocation("viewMatrix");
  }

  void bindAttributes() override
  {
    Shader::bindAttribute(0, "position");
  }
};

#endif
