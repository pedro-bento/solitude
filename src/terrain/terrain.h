#ifndef TERRAIN_H
#define TERRAIN_H

#include "../models/raw_model.h"
#include "../textures/terrain_texture_pack.h"
#include "../textures/terrain_texture.h"
#include "../utilities/load.h"

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <tuple>
#include <cmath>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

class Terrain
{
  const float SIZE = 1024;
  const float VERTEX_COUNT = SIZE/16;
  const float MAX_HEIGHT = 50;

  float x;
  float z;

  vector<float> heights;

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

private:
  const uint8_t perm[256] =
  {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
    36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
    234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
    88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
    134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
    230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
    1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
    116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
    124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
    47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
    154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
    108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
    242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
    239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
    50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
    141, 128, 195, 78, 66, 215, 61, 156, 180
  };

  float mFrequency = 0.01f;
  float mAmplitude = 1.0f;
  float mLacunarity = 2.0f;
  float mPersistence = 1.0f/mLacunarity;
  int mOctaves = 16;

  // Fractal Brownian Motion
  float fractal(size_t octaves, float x, float y);
  // perling noise
  float noise(float x, float y);
  inline int32_t fastfloor(float fp);
  inline uint8_t hash(int32_t i);
  float grad(int32_t hash, float x, float y);
};

#endif
