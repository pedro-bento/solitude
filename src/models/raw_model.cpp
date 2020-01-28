#include "raw_model.h"

RawModel::RawModel(GLuint _vaoID, GLuint _verticesID,
	GLuint _indicesID, GLuint _textureCoordsID,
	GLuint _normalsID, GLsizei _vertexCount)
	: vaoID(_vaoID), verticesID(_verticesID),
	indicesID(_indicesID), textureCoordsID(_textureCoordsID),
	normalsID(_normalsID), vertexCount(_vertexCount)
{
}

RawModel::~RawModel()
{
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &verticesID);
	glDeleteBuffers(1, &indicesID);
	glDeleteBuffers(1, &textureCoordsID);
}
