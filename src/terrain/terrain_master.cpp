#include "terrain_master.h"

TerrainMaster::TerrainMaster()
: backTexture(loadDDS("./res/grassy2.dds")),
  rTexture(loadDDS("./res/mud.dds")),
  gTexture(loadDDS("./res/grassFlowers.dds")),
  bTexture(loadDDS("./res/path.dds")),
  texturePack(&backTexture, &rTexture, &gTexture, &bTexture),
  blendMap(loadDDS("./res/blendMap.dds"))
{
  terrains["(0,0)"] = make_unique<Terrain>(0,0,&texturePack, &blendMap,
    &noise,SIZE,VERTEX_COUNT,MAX_HEIGHT);
  terrains["(-1,0)"] = make_unique<Terrain>(-1,0,&texturePack, &blendMap,
    &noise,SIZE,VERTEX_COUNT,MAX_HEIGHT);
  terrains["(0,-1)"] = make_unique<Terrain>(0,-1,&texturePack, &blendMap,
    &noise,SIZE,VERTEX_COUNT,MAX_HEIGHT);
  terrains["(-1,-1)"] = make_unique<Terrain>(-1,-1,&texturePack, &blendMap,
    &noise,SIZE,VERTEX_COUNT,MAX_HEIGHT);
}

TerrainMaster::~TerrainMaster()
{
}

Terrain* TerrainMaster::getTerrain(float x, float z)
{
  float xOffset = x < 0.0f ? -1.0f : 0.0f;
  float zOffset = z < 0.0f ? -1.0f : 0.0f;

  int gridX = (int)((x / SIZE) + xOffset);
  int gridZ = (int)((z / SIZE) + zOffset);

  string pos = "(" + to_string(gridX) + "," + to_string(gridZ) + ")";

  return terrains[pos].get();
}
