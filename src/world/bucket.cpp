#include "bucket.h"
#include "../config.h"

Bucket::Bucket(int worldX, int worldZ, PerlinNoise* noise, TerrainTexturePack* pack,
  TerrainTexture* blendMap, MasterRenderer* _renderer)
: terrain(worldX/config.bucketSize, worldZ/config.bucketSize,
    pack, blendMap, noise),
  renderer(_renderer)
{
  shared_ptr<TexturedModel> tree =
    loadTexturedModel("./res/pine.obj","./res/pine.dds");
  tree->getModelTexture()->setHasTransparency(true);

  shared_ptr<TexturedModel> poly =
    loadTexturedModel("./res/lowPolyTree.obj","./res/lowPolyTree.dds");

  shared_ptr<TexturedModel> fern =
    loadTexturedModel("./res/fern.obj","./res/fern.dds");
  fern->getModelTexture()->setNumberOfRows(2);

  float x;
  float z;

  for(int i = 0; i < 20; i++)
  {
    x = Random::randomFloat(worldX, worldX + config.bucketSize);
    z = Random::randomFloat(worldZ, worldZ + config.bucketSize);
    entities.push_back(make_unique<Entity>(
      tree,vec3(x,terrain.getHeightOfTerrain(x,z),z),
      vec3(0.0f,0.0f,0.0f),2.0f));

    x = Random::randomFloat(worldX, worldX + config.bucketSize);
    z = Random::randomFloat(worldZ, worldZ + config.bucketSize);
    entities.push_back(make_unique<Entity>(
      poly,vec3(x,terrain.getHeightOfTerrain(x,z),z),
      vec3(0.0f,0.0f,0.0f),1.0f));
  }

  for(int i = 0; i < 300; i++)
  {
    x = Random::randomFloat(worldX, worldX + config.bucketSize);
    z = Random::randomFloat(worldZ, worldZ + config.bucketSize);
    entities.push_back(make_unique<Entity>(
      fern,vec3(x,terrain.getHeightOfTerrain(x,z),z),
      vec3(0.0f,0.0f,0.0f),0.8f,Random::randomInt(0,4)));
  }

  if(worldX/config.bucketSize == 0 && worldZ/config.bucketSize == 0)
  {
    shared_ptr<TexturedModel> lamp =
      loadTexturedModel("./res/lamp.obj","./res/lamp.dds");

    entities.push_back(make_unique<Entity>(
      lamp,vec3(10,terrain.getHeightOfTerrain(worldX+10,worldX+10),10),
      vec3(0.0f,0.0f,0.0f),1.0f));
  }
}

Bucket::~Bucket()
{
}

void Bucket::render()
{
  renderer->processTerrain(&terrain);
  for(auto entity : entities)
    renderer->processEntity(entity.get());
}
