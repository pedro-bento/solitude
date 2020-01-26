#include "model_texture.h"

ModelTexture::ModelTexture(GLuint _textureID, GLuint _textureCoordsID, GLuint _normalsID)
: textureID(_textureID),
	textureCoordsID(_textureCoordsID),
	normalsID(_normalsID)
{
}

ModelTexture::~ModelTexture()
{
	glDeleteTextures(1, &textureID);
	glDeleteBuffers(1, &textureCoordsID);
}
