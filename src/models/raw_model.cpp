#include "raw_model.h"

RawModel::RawModel(GLuint _vaoID, GLuint _verticesID, GLuint _indicesID, GLsizei _vertexCount)
	: vaoID(_vaoID), verticesID(_verticesID), indicesID(_indicesID), vertexCount(_vertexCount)
{
}

RawModel::~RawModel()
{
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &verticesID);
	glDeleteBuffers(1, &indicesID);
}
