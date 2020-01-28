#include "model_texture.h"

ModelTexture::ModelTexture(GLuint _textureID)
: textureID(_textureID)
{
}

ModelTexture::~ModelTexture()
{
	glDeleteTextures(1, &textureID);
}
