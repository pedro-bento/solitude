#include "world.h"
#include "../config.h"
#include "../utilities/maths.h"

World::World(Window* _window)
: window(_window),
  renderer(window->getWidth()/window->getHeight()),
  player(window),
  texturePack("./res/grass.dds", "./res/mud.dds", "./res/grassFlowers.dds", "./res/grassy2.dds"),
  blendMap(loadDDS("./res/blendMap.dds"))
{
  buckets["(0,0)"] = make_unique<Bucket>(0, 0, &noise, &texturePack, &blendMap, &renderer);

  lights.push_back(make_unique<Light>(
    vec3(0.0f,1000.0f,300.0f), vec3(0.4f,0.4f,0.4f)));
  lights.push_back(make_unique<Light>(
    vec3(10.0f,getBucket(10.0f,10.0f)->getTerrain()->getHeightOfTerrain(10.0f,10.0f)+10,10.0f),
    vec3(1.0f,1.0f,1.0f), vec3(1.0f,0.01f,0.002f)));

  guis.push_back(make_unique<GuiTexture>(
    loadDDS("./res/health.dds"), vec2(-0.75f, 0.9f), vec2(0.2f, 0.2f)));
  guis.push_back(make_unique<GuiTexture>(
    loadDDS("./res/crosshair.dds"), vec2(0.0f, 0.0f), vec2(0.04f, 0.04f)));
}

World::~World()
{
}

Bucket* World::getBucket(float x, float z)
{
  float xOffset = x < 0.0f ? -1.0f : 0.0f;
  float zOffset = z < 0.0f ? -1.0f : 0.0f;

  int gridX = (int)((x / config.bucketSize) + xOffset);
  int gridZ = (int)((z / config.bucketSize) + zOffset);

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

  vec3 p = player.getPosition();
  getBucket(p.x,p.z)->render();

  for(auto& it : buckets)
    it.second->render();

  renderer.render(lights_ptr, &player);
  gui_renderer.render(guis_ptr);
}

void World::update()
{
  vec3 p = player.getPosition();
  player.move(getBucket(p.x,p.z)->getTerrain(),
              window->getElapsedTime());
}
