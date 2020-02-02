#ifndef TERRAIN_H
#define TERRAIN_H

#include "../models/raw_model.h"
#include "../textures/model_texture.h"
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
  shared_ptr<ModelTexture> model_texture;

public:
  Terrain(int gridX, int gridZ, shared_ptr<ModelTexture> texture);
  ~Terrain();

  float getX() { return x; }
  float getZ() { return z; }

  shared_ptr<RawModel> getRawModel() { return raw_model; }
  shared_ptr<ModelTexture> getModelTexture() { return model_texture; }

  shared_ptr<RawModel> generateTerrain();
};

#endif
