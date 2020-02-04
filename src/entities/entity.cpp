#include "entity.h"

Entity::Entity(shared_ptr<TexturedModel> _textured_model,
	vec3 _position, vec3 _rotation, float _scale)
	: textured_model(_textured_model),
		position(_position), rotation(_rotation), scale(_scale)
{
}

Entity::Entity(shared_ptr<TexturedModel> _textured_model,
	vec3 _position, vec3 _rotation, float _scale, int _textureIndex)
	: textured_model(_textured_model), position(_position),
	  rotation(_rotation), scale(_scale), textureIndex(_textureIndex)
{
}

Entity::~Entity()
{
}

void Entity::move(vec3 dxyz)
{
	position += dxyz;
}

void Entity::rotate(vec3 dxyz)
{
	rotation += dxyz;
}

float Entity::getTextureXOffset()
{
	int column = textureIndex % textured_model->getModelTexture()->getNumberOfRows();
	return (float)column/(float)textured_model->getModelTexture()->getNumberOfRows();
}

float Entity::getTextureYOffset()
{
	int row = textureIndex / textured_model->getModelTexture()->getNumberOfRows();
	return (float)row/(float)textured_model->getModelTexture()->getNumberOfRows();
}
