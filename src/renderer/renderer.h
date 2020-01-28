#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

#include "../models/raw_model.h"
#include "../models/textured_model.h"
#include "../textures/model_texture.h"
#include "../entities/entity.h"
#include "../shaders/static_shader.h"
#include "../utilities/maths.h"
#include "../shaders/static_shader.h"

class Renderer
{
  mat4 projectionMatrix;
  StaticShader* static_shader;

public:
  Renderer(StaticShader* _static_shader, float fov, float aspectRatio, float nearPlane, float farPlane);
  ~Renderer();

  void prepare();
  void render(unordered_map<shared_ptr<TexturedModel>,
                vector<Entity*>> entities);

private:
  void prepareTexturedModel(shared_ptr<TexturedModel> textured_model);
  void unbindTexturedModel();
  void prepareInstance(Entity* entity);
};

#endif // RENDERER_H
