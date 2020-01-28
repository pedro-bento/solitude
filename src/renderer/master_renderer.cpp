#include "master_renderer.h"

MasterRenderer::MasterRenderer(float aspectRatio)
: renderer(&static_shader, 70, aspectRatio, 0.1f, 100.0f)
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::render(Light* sun, Camera* camera)
{
  renderer.prepare();
  static_shader.start();
  static_shader.loadLight(sun),
  static_shader.loadViewMatrix(camera);
  renderer.render(entities);
  static_shader.stop();
  entities.clear();
}

void MasterRenderer::processEntity(Entity* entity)
{
  shared_ptr<TexturedModel> entityModel = entity->getTexturedModel();
  auto search = entities.find(entityModel);
  if(search != entities.end())
  {
    entities[entityModel].push_back(entity);
  }
  else
  {
    vector<Entity*> batch = {entity};
    entities.insert({entityModel, batch});
  }
}
