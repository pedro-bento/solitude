#ifndef MASTER_RENDERER
#define MASTER_RENDERER

#include "../shaders/static_shader.h"
#include "renderer.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;
#include "../models/textured_model.h"
#include "../entities/entity.h"
#include "../entities/light.h"
#include "../entities/camera.h"

class MasterRenderer
{
  StaticShader static_shader;
  Renderer renderer;
  unordered_map<shared_ptr<TexturedModel>, vector<Entity*>> entities;

public:
  MasterRenderer(float aspectRatio);
  ~MasterRenderer();

  void render(Light* sun, Camera* camera);
  void processEntity(Entity* entity);
};

#endif
