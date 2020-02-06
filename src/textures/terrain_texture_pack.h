#ifndef TERRAIN_TEXTURE_PACK_H
#define TERRAIN_TEXTURE_PACK_H

#include "terrain_texture.h"
#include "../utilities/load.h"

class TerrainTexturePack
{
  TerrainTexture backTexture;
  TerrainTexture rTexture;
  TerrainTexture gTexture;
  TerrainTexture bTexture;

public:
  TerrainTexturePack(
    const char * _backTexture,
    const char * _rTexture,
    const char * _gTexture,
    const char * _bTexture)
  : backTexture(loadDDS(_backTexture)),
    rTexture(loadDDS(_rTexture)),
    gTexture(loadDDS(_gTexture)),
    bTexture(loadDDS(_bTexture)) {}
    ~TerrainTexturePack() {}

    TerrainTexture* getBackTexture() { return &backTexture; }
    TerrainTexture* getRTexture() { return &rTexture; }
    TerrainTexture* getGTexture() { return &gTexture; }
    TerrainTexture* getBTexture() { return &bTexture; }
};

#endif
