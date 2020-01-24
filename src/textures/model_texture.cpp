#include "model_texture.h"

ModelTexture::ModelTexture(GLuint _textureID, GLuint _textureCoordsID)
: textureID(_textureID), textureCoordsID(_textureCoordsID)
{
}

ModelTexture::~ModelTexture()
{
	glDeleteTextures(1, &textureID);
	glDeleteBuffers(1, &textureCoordsID);
}
