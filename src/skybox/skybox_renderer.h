#ifndef SKYBOX_RENDERER_H
#define SKYBOX_RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
using namespace std;

#include "../models/simple_model.h"
#include "skybox_shader.h"
#include "../utilities/load.h"
#include "../entities/fpp_camera.h"
#include "../config.h"

class SkyboxRenderer
{
  float SIZE = config.viewDistance/1.74f;
	vector<GLfloat> VERTICES{
	    -SIZE,  SIZE, -SIZE,
	    -SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,
	     SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,

	    -SIZE, -SIZE,  SIZE,
	    -SIZE, -SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE, -SIZE,
	    -SIZE,  SIZE,  SIZE,
	    -SIZE, -SIZE,  SIZE,

	     SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,

	    -SIZE, -SIZE,  SIZE,
	    -SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE, -SIZE,  SIZE,
	    -SIZE, -SIZE,  SIZE,

	    -SIZE,  SIZE, -SIZE,
	     SIZE,  SIZE, -SIZE,
	     SIZE,  SIZE,  SIZE,
	     SIZE,  SIZE,  SIZE,
	    -SIZE,  SIZE,  SIZE,
	    -SIZE,  SIZE, -SIZE,

	    -SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE,  SIZE,
	     SIZE, -SIZE, -SIZE,
	     SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE,  SIZE,
	     SIZE, -SIZE,  SIZE
	};

  vector<char*> TEXTURE_FILES{
    "./res/right.png",
    "./res/left.png",
    "./res/top.png",
    "./res/bottom.png",
    "./res/back.png",
    "./res/front.png"
  };

  SimpleModel cube;
  GLuint textureID;
  SkyboxShader shader;

public:
  SkyboxRenderer(mat4 projectionMaxtrix)
  : cube(loadSimpleModel(VERTICES, 3)),
    textureID(loadCubeMap(TEXTURE_FILES))
  {
    shader.start();
    shader.loadProjectionMatrix(projectionMaxtrix);
    shader.stop();
  }

  void render(FPPCamera* camera)
  {
    shader.start();
    shader.loadViewMatrix(camera);
    glBindVertexArray(cube.getVaoID());
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, cube.getVerticesID());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawArrays(GL_TRIANGLES,0,cube.getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader.stop();
  }

};

#endif
