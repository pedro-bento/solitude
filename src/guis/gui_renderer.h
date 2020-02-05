#ifndef GUI_RENDERER
#define GUI_RENDERER

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include "../models/simple_model.h"
#include "../utilities/load.h"
#include "gui_texture.h"
#include "gui_shader.h"

#include <vector>
#include <memory>
using namespace std;

class GuiRenderer
{
  SimpleModel quad;
  GuiShader shader;

public:
  GuiRenderer() : quad(loadSimpleModel(
    vector<GLfloat>{ -1.0f,1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f,-1.0f})){}
  ~GuiRenderer() {}

  void render(vector<GuiTexture*> guis)
  {
    shader.start();
    glBindVertexArray(quad.getVaoID());
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quad.getVerticesID());
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for(auto gui : guis)
    {
      glActiveTexture(GL_TEXTURE0);
    	glBindTexture(GL_TEXTURE_2D, gui->getTextureID());
      mat4 matrix = createTransformationMatrix(gui->getPosition(), gui->getScale());
      shader.loadTransformation(matrix);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
    }
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader.stop();
  }
};

#endif
