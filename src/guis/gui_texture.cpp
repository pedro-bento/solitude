#include "gui_texture.h"

GuiTexture::GuiTexture(GLuint _textureID, vec2 _position, vec2 _scale)
: textureID(_textureID), position(_position), scale(_scale)
{
}

GuiTexture::~GuiTexture()
{
  glDeleteTextures(1, &textureID);
}
