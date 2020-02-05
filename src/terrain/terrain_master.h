#ifndef TERRAIN_MASTER_H
#define TERRAIN_MASTER_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

#include "../textures/terrain_texture.h"
#include "../textures/terrain_texture_pack.h"
#include "terrain.h"
#include "../utilities/maths.h"

class TerrainMaster
{
  const float SIZE = 1024;
  const float VERTEX_COUNT = SIZE/8.0f;
  const float MAX_HEIGHT = 200;

  PerlinNoise noise;
  TerrainTexture backTexture;
  TerrainTexture rTexture;
  TerrainTexture gTexture;
  TerrainTexture bTexture;
  TerrainTexturePack texturePack;
  TerrainTexture blendMap;
  unordered_map<string, unique_ptr<Terrain>> terrains;

public:
  TerrainMaster();
  ~TerrainMaster();

  Terrain* getTerrain(float x, float z);

private:
  void createTerrains();
};

#endif
