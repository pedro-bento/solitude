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
  Bucket(int worldX, int worldZ, int size, int vertex_count, int max_height,
    PerlinNoise* noise, TerrainTexturePack* pack, TerrainTexture* blendMap,
    MasterRenderer* _renderer)
  : terrain(worldX/size, worldZ/size, pack, blendMap, noise,
            size, vertex_count, max_height),
    renderer(_renderer)
  {
    shared_ptr<TexturedModel> tree =
      loadTexturedModel("./res/pine.obj","./res/pine.dds");

    for(int i = 0; i < 6; i++)
    {
      float x = Random::randomFloat(worldX, worldX + size);
      float z = Random::randomFloat(worldZ, worldZ + size);
      entities.push_back(make_unique<Entity>(
        tree,vec3(x,terrain.getHeightOfTerrain(x,z),z),
        vec3(0.0f,0.0f,0.0f),1.0f));
    }
  }

  ~Bucket()
  {
  }

  int getGridX() { return terrain.getX(); }
  int getGridZ() { return terrain.getZ(); }
  Terrain* getTerrain() { return &terrain; }

  void render()
  {
    renderer->processTerrain(&terrain);
    for(auto entity : entities)
      renderer->processEntity(entity.get());
  }
};

#endif
