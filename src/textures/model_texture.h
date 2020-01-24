#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>

class ModelTexture
{
	GLuint textureID;
	GLuint textureCoordsID;

public:
	ModelTexture(GLuint _textureID, GLuint _textureCoordsID);
	~ModelTexture();

  GLuint getTextureID() { return textureID; }
	GLuint getTextureCoordsID() { return textureCoordsID; }
};

#endif // MODEL_TEXTURE_H
