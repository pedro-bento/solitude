#include "master_renderer.h"

MasterRenderer::MasterRenderer(float aspectRatio)
: skyColour(0.53f, 0.81f, 0.98f),
	projectionMatrix(perspective(radians(70.0f), aspectRatio, 0.1f, 512.0f)),
	entity_renderer(&static_shader, projectionMatrix),
	terrain_renderer(&terrain_shader, projectionMatrix)
{
	enableCulling();
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(skyColour.x, skyColour.y, skyColour.z, 1.0f);
}

void MasterRenderer::render(Light* sun, FPPCamera* camera)
{
  prepare();

  static_shader.start();
	static_shader.loadSkyColour(skyColour);
  static_shader.loadLight(sun),
  static_shader.loadViewMatrix(camera);
  entity_renderer.render(entities);
  static_shader.stop();

	terrain_shader.start();
	terrain_shader.loadSkyColour(skyColour);
	terrain_shader.loadLight(sun),
  terrain_shader.loadViewMatrix(camera);
	terrain_renderer.render(terrains);
	terrain_shader.stop();

	terrains.clear();
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

void MasterRenderer::processTerrain(Terrain* terrain)
{
	terrains.push_back(terrain);
}
