#ifndef MASTER_RENDERER
#define MASTER_RENDERER

#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "../shaders/static_shader.h"
#include "entity_renderer.h"
#include "../models/textured_model.h"
#include "../entities/entity.h"
#include "../entities/light.h"
#include "../entities/camera.h"


class MasterRenderer
{
  mat4 projectionMatrix;
  StaticShader static_shader;
  EntityRenderer entity_renderer;
  unordered_map<shared_ptr<TexturedModel>, vector<Entity*>> entities;

public:
  MasterRenderer(float aspectRatio);
  ~MasterRenderer();

  void prepare();
  void render(Light* sun, Camera* camera);
  void processEntity(Entity* entity);
};

#endif
