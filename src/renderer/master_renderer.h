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
#include "../entities/fpp_camera.h"
#include "terrain_renderer.h"
#include "../shaders/terrain_shader.h"
#include "../terrain/terrain.h"

class MasterRenderer
{
  vec3 skyColour;
  mat4 projectionMatrix;
  StaticShader static_shader;
  EntityRenderer entity_renderer;
  TerrainShader terrain_shader;
  TerrainRenderer terrain_renderer;

  unordered_map<shared_ptr<TexturedModel>, vector<Entity*>> entities;
  vector<Terrain*> terrains;

public:
  MasterRenderer(float aspectRatio);
  ~MasterRenderer();

  static void enableCulling()
  {
    glEnable(GL_CULL_FACE);
  	glCullFace(GL_BACK);
  }

  static void disableCulling()
  {
    glDisable(GL_CULL_FACE);
  }

  void prepare();
  void render(Light* sun, FPPCamera* camera);
  void processEntity(Entity* entity);
  void processTerrain(Terrain* terrain);
};

#endif
