#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

#include "bucket.h"
#include "../window.h"
#include "../utilities/load.h"
#include "../renderer/master_renderer.h"
#include "../entities/fpp_camera.h"
#include "../entities/light.h"
#include "../textures/terrain_texture.h"
#include "../textures/terrain_texture_pack.h"
#include "../guis/gui_texture.h"
#include "../guis/gui_renderer.h"

class World
{
  PerlinNoise noise;
  TerrainTexturePack texturePack;
  TerrainTexture blendMap;

  Window* window;
  FPPCamera player;
  MasterRenderer renderer;
  GuiRenderer gui_renderer;
  unordered_map<string, unique_ptr<Bucket>> buckets;
  vector<unique_ptr<Light>> lights;
  vector<unique_ptr<GuiTexture>> guis;

public:
  World(Window* _window);
  ~World();

  Bucket* getBucket(float x, float z);
  void render();
  void update();
};

#endif
