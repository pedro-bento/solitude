#include "world.h"
#include "../config.h"
#include "../utilities/maths.h"

World::World(Window* _window)
: window(_window),
  renderer(window->getWidth()/window->getHeight()),
  player(window),
  texturePack("./res/grassy2.dds", "./res/mud.dds", "./res/grassFlowers.dds", "./res/path.dds"),
  blendMap(loadDDS("./res/blendMap.dds"))
{
  lights.push_back(make_unique<Light>(
    vec3(0.0f,100000.0f,-3000.0f), vec3(1.0f,1.0f,1.0f)));
  lights.push_back(make_unique<Light>(
    vec3(10.0f,getBucket(10.0f,10.0f)->getTerrain()->getHeightOfTerrain(10.0f,10.0f)+10,10.0f),
    vec3(1.0f,1.0f,1.0f), vec3(1.0f,0.01f,0.002f)));

  guis.push_back(make_unique<GuiTexture>(
    loadDDS("./res/health.dds"), vec2(-0.75f, 0.9f), vec2(0.2f, 0.2f)));
  guis.push_back(make_unique<GuiTexture>(
    loadDDS("./res/crosshair.dds"), vec2(0.0f, 0.0f), vec2(0.04f, 0.04f)));

  for(int i = -2; i <= 2; i++)
    for(int j = -2; j <= 2; j++)
    {
      getBucketGrid(i,j);
    }
}

World::~World()
{
}

vec2 World::getGridPos(float worldX, float worldZ)
{
  float xOffset = worldX < 0.0f ? -1.0f : 0.0f;
  float zOffset = worldZ < 0.0f ? -1.0f : 0.0f;

  int gridX = (int)((worldX / config.bucketSize) + xOffset);
  int gridZ = (int)((worldZ / config.bucketSize) + zOffset);

  return vec2(gridX, gridZ);
}

Bucket* World::getBucket(float x, float z)
{
  vec2 gridPos = getGridPos(x,z);

  string pos = "(" + to_string(gridPos.x) + "," + to_string(gridPos.y) + ")";

  if(buckets.find(pos) == buckets.end())
    buckets[pos] = make_unique<Bucket>(gridPos.x*config.bucketSize,
      gridPos.y*config.bucketSize, &noise, &texturePack,
      &blendMap, &renderer);

  return buckets[pos].get();
}

Bucket* World::getBucketGrid(int gridX, int gridZ)
{
  string pos = "(" + to_string(gridX) + "," + to_string(gridZ) + ")";

  if(buckets.find(pos) == buckets.end())
    buckets[pos] = make_unique<Bucket>(gridX*config.bucketSize,
      gridZ*config.bucketSize, &noise, &texturePack,
      &blendMap, &renderer);

  return buckets[pos].get();
}

void World::render()
{
  vector<Light*> lights_ptr;
  for(int i = 0; i < 4; i++)
  {
    if(i < lights.size())
      lights_ptr.push_back(lights[i].get());
    else
      break;
  }

  vector<GuiTexture*> guis_ptr;
  for(auto& gui : guis)
  {
    guis_ptr.push_back(gui.get());
  }

  vec3 pos = player.getPosition();
  vec2 grid = getGridPos(pos.x, pos.z);

  getBucketGrid(grid.x, grid.y)->render();

  getBucketGrid(grid.x-1, grid.y)->render();
  getBucketGrid(grid.x+1, grid.y)->render();
  getBucketGrid(grid.x, grid.y-1)->render();
  getBucketGrid(grid.x, grid.y+1)->render();

  getBucketGrid(grid.x-1, grid.y-1)->render();
  getBucketGrid(grid.x-1, grid.y+1)->render();
  getBucketGrid(grid.x+1, grid.y-1)->render();
  getBucketGrid(grid.x+1, grid.y+1)->render();

  renderer.render(lights_ptr, &player);
  gui_renderer.render(guis_ptr);
}

void World::update()
{
  vec3 p = player.getPosition();
  player.move(getBucket(p.x,p.z)->getTerrain(),
              window->getElapsedTime());
}
