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
#include <memory>
using namespace std;

#include "../models/raw_model.h"
#include "../textures/model_texture.h"
#include "../models/textured_model.h"
#include "../models/simple_model.h"

GLuint loadShader(const char* shaderPath, GLenum shader);
shared_ptr<RawModel> loadRawModel(vector<GLfloat> vertices, vector<unsigned short> indices, vector<GLfloat> uvs, vector<GLfloat> normals);
SimpleModel loadSimpleModel(vector<GLfloat> vertices);
shared_ptr<ModelTexture> loadModelTexture(const char* texturePath);
shared_ptr<TexturedModel> loadTexturedModel(const char* objPath, const char* texturePath);
GLuint loadDDS(const char * imagepath);
bool loadAssImp(const char * path, vector<unsigned short> & indices, vector<GLfloat> & vertices, vector<GLfloat> & uvs, vector<GLfloat> & normals);

#endif // LOAD_H
