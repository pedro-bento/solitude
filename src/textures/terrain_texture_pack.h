#ifndef TERRAIN_TEXTURE_PACK_H
#define TERRAIN_TEXTURE_PACK_H

#include "terrain_texture.h"

class TerrainTexturePack
{
  TerrainTexture* backTexture;
  TerrainTexture* rTexture;
  TerrainTexture* gTexture;
  TerrainTexture* bTexture;

public:
  TerrainTexturePack(
    TerrainTexture* _backTexture,
    TerrainTexture* _rTexture,
    TerrainTexture* _gTexture,
    TerrainTexture* _bTexture)
  : backTexture(_backTexture),
    rTexture(_rTexture),
    gTexture(_gTexture),
    bTexture(_bTexture) {}
    ~TerrainTexturePack() {}

    TerrainTexture* getBackTexture() { return backTexture; }
    TerrainTexture* getRTexture() { return rTexture; }
    TerrainTexture* getGTexture() { return gTexture; }
    TerrainTexture* getBTexture() { return bTexture; }
};

#endif
