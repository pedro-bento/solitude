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
  const float SIZE = 1024;
  const float VERTEX_COUNT = SIZE/8;
  const float MAX_HEIGHT = 100;

  float x;
  float z;

  vector<vector<float>> heights;
  PerlinNoise noise;

  shared_ptr<RawModel> raw_model;
  TerrainTexturePack* texturePack;
  TerrainTexture* blendMap;

public:
  Terrain(int gridX, int gridZ, TerrainTexturePack* _texturePack, TerrainTexture* _blendMap);
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
