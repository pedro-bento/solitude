#ifndef LOAD_H
#define LOAD_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "../models/raw_model.h"
#include "../textures/model_texture.h"

GLuint loadShader(const char* shaderPath, GLenum shader);
RawModel loadRawModel(vector<GLfloat> vertices, vector<unsigned int> indices);
ModelTexture loadModelTexture(vector<GLfloat> textureCoords, const char* texturePath);
GLuint loadBMP(const char* texturePath);

#endif // LOAD_H
