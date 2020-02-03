#ifndef MATHS_H
#define MATHS_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "../entities/fpp_camera.h"

mat4 createTransformationMatrix(vec3 translation, vec3 rotation, float scale);
mat4 createViewMatrix(FPPCamera* camera);
float barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos);

#endif
