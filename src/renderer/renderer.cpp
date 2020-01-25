#include "renderer.h"

Renderer::Renderer(float _fov, float _aspectRatio, float _nearPlane,
                   float _farPlane, StaticShader* static_shader)
{
  projectionMatrix = perspective(radians(_fov), _aspectRatio, _nearPlane, _farPlane);
  static_shader->start();
  static_shader->loadProjectionMatrix(projectionMatrix);
  static_shader->stop();
}

Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
}

void Renderer::render(Entity* entity, StaticShader* static_shader)
{
  TexturedModel* textured_model = entity->getTexturedModel();
	RawModel* raw_model = textured_model->getRawModel();
  ModelTexture* model_texture = textured_model->getModelTexture();

	glBindVertexArray(raw_model->getVaoID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model_texture->getTextureID());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, raw_model->getVerticesID());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, model_texture->getTextureCoordsID());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, raw_model->getIndicesID());

	mat4 transformationMatrix = createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
	static_shader->loadTransformationMatrix(transformationMatrix);

	glDrawElements(GL_TRIANGLES, raw_model->getVertexCount(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}
