#include "terrain_renderer.h"

TerrainRenderer::TerrainRenderer(
  TerrainShader* _terrain_shader,
  mat4 projectionMatrix)
: terrain_shader(_terrain_shader)
{
  terrain_shader->start();
  terrain_shader->loadProjectionMatrix(projectionMatrix);
  terrain_shader->stop();
}

void TerrainRenderer::render(vector<Terrain*> terrains)
{
  for(auto terrain : terrains)
  {
    prepareTerrain(terrain);
    loadModelMatrix(terrain);
    glDrawElements(
      GL_TRIANGLES,
      terrain->getRawModel()->getVertexCount(),
      GL_UNSIGNED_INT,
      NULL);
    unbindTexturedModel();
  }
}

void TerrainRenderer::prepareTerrain(Terrain* terrain)
{
	glBindVertexArray(terrain->getRawModel()->getVaoID());

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
    terrain->getRawModel()->getIndicesID());

  terrain_shader->loadShineVariables(
    terrain->getModelTexture()->getShineDamper(),
    terrain->getModelTexture()->getReflectivity());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,
    terrain->getModelTexture()->getTextureID());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,
    terrain->getRawModel()->getVerticesID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,
    terrain->getRawModel()->getTextureCoordsID());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER,
    terrain->getRawModel()->getNormalsID());
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void TerrainRenderer::unbindTexturedModel()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain* terrain)
{
  mat4 transformationMatrix = createTransformationMatrix(
    vec3(terrain->getX(), 0, terrain->getZ()),
    vec3(0.0f,0.0f,0.0f), 1.0f);
	terrain_shader->loadTransformationMatrix(transformationMatrix);
}
