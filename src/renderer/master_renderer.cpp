#include "master_renderer.h"

MasterRenderer::MasterRenderer(float aspectRatio)
: projectionMatrix(perspective(radians(70.0f), aspectRatio, 0.1f, 100.0f)),
	entity_renderer(&static_shader, projectionMatrix)
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
}

void MasterRenderer::render(Light* sun, Camera* camera)
{
  prepare();
  static_shader.start();
  static_shader.loadLight(sun),
  static_shader.loadViewMatrix(camera);
  entity_renderer.render(entities);
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
