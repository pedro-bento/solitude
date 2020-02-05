#ifndef TERRAIN_H
#define TERRAIN_H

#include "../models/raw_model.h"
#include "../textures/terrain_texture_pack.h"
#include "../textures/terrain_texture.h"
#include "../utilities/load.h"
#include "../utilities/maths.h"

#include <vector>
#include <cmath>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

class Terrain
{
  float SIZE = 1;
  float VERTEX_COUNT = 1;
  float MAX_HEIGHT = 1;

  float x, z;
  float xOffset, zOffset;

  shared_ptr<RawModel> raw_model;
  TerrainTexturePack* texturePack;
  TerrainTexture* blendMap;
  PerlinNoise* noise;
  vector<vector<float>> heights;

public:
  Terrain(int gridX, int gridZ, TerrainTexturePack* _texturePack,
    TerrainTexture* _blendMap, PerlinNoise* _noise,
    float size, float vertex_count, float max_height);
  ~Terrain();

  float getX() { return x; }
  float getZ() { return z; }

  float getHeightOfTerrain(float worldX, float worldZ);

  shared_ptr<RawModel> getRawModel() { return raw_model; }
  TerrainTexturePack* getTexturePack() { return texturePack; }
  TerrainTexture* getBlendMap() { return blendMap; }

private:
  shared_ptr<RawModel> generateTerrain();
  vec3 calculateNormal(int x, int z);
  float getHeight(int x, int z);
};

#endif
