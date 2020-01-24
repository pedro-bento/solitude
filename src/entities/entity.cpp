#include "entity.h"

Entity::Entity()
	: textured_model(NULL),
	position(vec3(0.0f)), rotation(vec3(0.0f)), scale(0.0f)
{	
}

Entity::Entity(TexturedModel* _textured_model,
	vec3 _position, vec3 _rotation, float _scale)
	: textured_model(_textured_model),
		position(_position), rotation(_rotation), scale(_scale)
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
