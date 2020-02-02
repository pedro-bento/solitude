#ifndef TERRAIN_TEXTURE_H
#define TERRAIN_TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>

class TerrainTexture
{
  GLuint textureID;

public:
  TerrainTexture(GLuint _textureID) : textureID(_textureID) {}
  ~TerrainTexture(){ glDeleteTextures(1, &textureID); }

  GLuint getTextureID() { return textureID; }
};

#endif
