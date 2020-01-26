#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>

class ModelTexture
{
	GLuint textureID;
	GLuint textureCoordsID;
	GLuint normalsID;

public:
	ModelTexture(GLuint _textureID, GLuint _textureCoordsID, GLuint _normalsID);
	~ModelTexture();

  GLuint getTextureID() { return textureID; }
	GLuint getTextureCoordsID() { return textureCoordsID; }
	GLuint getNormalsID() { return normalsID; }
};

#endif // MODEL_TEXTURE_H
