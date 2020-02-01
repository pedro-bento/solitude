#include "entity_renderer.h"
#include "master_renderer.h"

EntityRenderer::EntityRenderer(
  StaticShader* _static_shader,
  mat4 projectionMatrix)
: static_shader(_static_shader)
{
  static_shader->start();
  static_shader->loadProjectionMatrix(projectionMatrix);
  static_shader->stop();
}

EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::render(
  unordered_map<shared_ptr<TexturedModel>,
                vector<Entity*>> entities)
{
  for(auto it : entities)
  {
    prepareTexturedModel(it.first);
    auto search = entities.find(it.first);
    if(search != entities.end())
    {
      vector<Entity*> batch = search->second;
      for(auto entity : batch)
      {
        prepareInstance(entity);
        glDrawElements(
          GL_TRIANGLES,
          it.first->getRawModel()->getVertexCount(),
          GL_UNSIGNED_INT,
          NULL);
      }
      unbindTexturedModel();
    }
  }
}

void EntityRenderer::prepareTexturedModel(
  shared_ptr<TexturedModel> textured_model)
{
  if(textured_model->getModelTexture()->getHasTransparency())
  {
    MasterRenderer::disableCulling();
  }

	glBindVertexArray(textured_model->getRawModel()->getVaoID());

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
    textured_model->getRawModel()->getIndicesID());

  static_shader->loadShineVariables(
    textured_model->getModelTexture()->getShineDamper(),
    textured_model->getModelTexture()->getReflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,
    textured_model->getModelTexture()->getTextureID());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,
    textured_model->getRawModel()->getVerticesID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,
    textured_model->getRawModel()->getTextureCoordsID());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER,
    textured_model->getRawModel()->getNormalsID());
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void EntityRenderer::unbindTexturedModel()
{
  MasterRenderer::enableCulling();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity* entity)
{
  mat4 transformationMatrix = createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
	static_shader->loadTransformationMatrix(transformationMatrix);
}
