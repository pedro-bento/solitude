#ifndef TERRAIN_RENDERER
#define TERRAIN_RENDERER

#include <vector>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "../shaders/terrain_shader.h"
#include "../terrain/terrain.h"

class TerrainRenderer
{
  TerrainShader* terrain_shader;

public:
  TerrainRenderer(TerrainShader* _terrain_shader, mat4 projectionMatrix);
  ~TerrainRenderer() {}

  void render(vector<Terrain*> terrains);

private:
  void prepareTerrain(Terrain* terrain);
  void unbindTexturedModel();
  void loadModelMatrix(Terrain* terrain);
};

#endif
