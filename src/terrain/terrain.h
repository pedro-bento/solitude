#ifndef TERRAIN_H
#define TERRAIN_H

#include "../models/raw_model.h"
#include "../textures/terrain_texture_pack.h"
#include "../textures/terrain_texture.h"
#include "../utilities/load.h"

#include <vector>
using namespace std;

class Terrain
{
  const float SIZE = 800;
  const int VERTEX_COUNT = 128;

  float x;
  float z;

  shared_ptr<RawModel> raw_model;
  TerrainTexturePack* texturePack;
  TerrainTexture* blendMap;

public:
  Terrain(int gridX, int gridZ, TerrainTexturePack* _texturePack, TerrainTexture* _blendMap);
  ~Terrain();

  float getX() { return x; }
  float getZ() { return z; }

  shared_ptr<RawModel> getRawModel() { return raw_model; }
  TerrainTexturePack* getTexturePack() { return texturePack; }
  TerrainTexture* getBlendMap() { return blendMap; }

  shared_ptr<RawModel> generateTerrain();
};

#endif
