#ifndef SIMPLE_MODEL_H
#define SIMPLE_MODEL_H

#define GLEW_STATIC
#include <GL/glew.h>

class SimpleModel
{
	GLuint vaoID;
	GLuint verticesID;
	GLsizei vertexCount;

public:
	SimpleModel(GLuint _vaoID, GLuint _verticesID, GLsizei _vertexCount)
  : vaoID(_vaoID), verticesID(_verticesID), vertexCount(_vertexCount) {}

	~SimpleModel()
	{
		glDeleteVertexArrays(1, &vaoID);
		glDeleteBuffers(1, &verticesID);
	}

	GLuint getVaoID() { return vaoID; }
	GLuint getVerticesID() { return verticesID; }
	GLsizei getVertexCount() {return vertexCount; }

	SimpleModel(const SimpleModel& sm)
  {
    vaoID = sm.vaoID;
		verticesID = sm.verticesID;
		vertexCount = sm.vertexCount;
  }
};

#endif
