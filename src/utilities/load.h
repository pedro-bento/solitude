#ifndef LOAD_H
#define LOAD_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
bool loadAssImp(const char * path, vector<unsigned int> & indices, vector<GLfloat> & vertices, vector<GLfloat> & uvs, vector<GLfloat> & normals);

#endif // LOAD_H
