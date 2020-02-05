#ifndef GUI_SHADER
#define GUI_SHADER

#include "../shaders/shader.h"

class GuiShader : public Shader
{
  GLuint location_transformationMatrix;

public:
  GuiShader()
  : Shader("./glsl/guiVertexShader.glsl",
           "./glsl/guiFragmentShader.glsl")
  {
    getAllUniformLocations();
  }

  ~GuiShader() {}

  void loadTransformation(mat4 matrix)
  {
    Shader::loadMatrix(location_transformationMatrix, matrix);
  }

  void getAllUniformLocations() override
  {
    location_transformationMatrix = Shader::getUniformLocation("transformationMatrix");
  }

  void bindAttributes() override
  {
    Shader::bindAttribute(0, "position");
  }
};

#endif
