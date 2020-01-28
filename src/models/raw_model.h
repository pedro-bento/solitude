#ifndef RAW_MODEL_H
#define RAW_MODEL_H

#define GLEW_STATIC
#include <GL/glew.h>

class RawModel
{
	GLuint vaoID;
	GLuint verticesID;
	GLuint indicesID;
	GLuint textureCoordsID;
	GLuint normalsID;
	GLsizei vertexCount;

public:
	RawModel(GLuint _vaoID, GLuint _verticesID,
		GLuint _indicesID, GLuint _textureCoordsID,
		GLuint _normalsID, GLsizei _vertexCount);
	~RawModel();

	GLuint getVaoID() { return vaoID; }
	GLuint getVerticesID() { return verticesID; }
	GLuint getIndicesID() { return indicesID; }
	GLuint getTextureCoordsID() { return textureCoordsID; }
	GLuint getNormalsID() { return normalsID; }
	GLsizei getVertexCount() {return vertexCount; }
};

#endif // RAW_MODEL_H
