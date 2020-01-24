#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "../models/raw_model.h"
#include "../models/textured_model.h"
#include "../textures/model_texture.h"
#include "../entities/entity.h"
#include "../shaders/static_shader.h"
#include "../utilities/maths.h"

class Renderer
{
  mat4 projectionMatrix;

public:
  Renderer(float _fov, float _aspectRatio, float _nearPlane,
           float _farPlane, StaticShader* shader);
  ~Renderer();

  void prepare();
  void render(Entity* entity, StaticShader* static_shader);
};

#endif // RENDERER_H
