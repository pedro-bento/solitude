#ifndef GUI_TEXTURE_H
#define GUI_TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

class GuiTexture
{
  GLuint textureID;
  vec2 position;
  vec2 scale;

public:
  GuiTexture(GLuint textureID, vec2 position, vec2 scale);
  ~GuiTexture();

  GLuint getTextureID() { return textureID; }
  vec2 getPosition() { return position; }
  vec2 getScale() { return scale; }

  GuiTexture(const GuiTexture& gt)
  {
    textureID = gt.textureID;
    position.x = gt.position.x;
    position.y = gt.position.y;
    scale.y = gt.scale.y;
    scale.y = gt.scale.y;
  }
};

#endif
