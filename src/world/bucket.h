#ifndef BUCKET_H
#define BUCKET_H

#include <memory>
#include <vector>
using namespace std;

#include "../terrain/terrain.h"
#include "../entities/entity.h"
#include "../utilities/maths.h"
#include "../renderer/master_renderer.h"

class Bucket
{
  Terrain terrain;
  vector<shared_ptr<Entity>> entities;
  MasterRenderer* renderer;

public:
  Bucket(int worldX, int worldZ, PerlinNoise* noise, TerrainTexturePack* pack,
    TerrainTexture* blendMap, MasterRenderer* _renderer);
  ~Bucket();

  int getGridX() { return terrain.getX(); }
  int getGridZ() { return terrain.getZ(); }
  Terrain* getTerrain() { return &terrain; }
  void render();
};

#endif
