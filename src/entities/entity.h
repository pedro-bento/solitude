#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
using namespace glm;

#include "../models/textured_model.h"

class Entity
{
	TexturedModel* textured_model;
	vec3 position;
	vec3 rotation;
	float scale;

public:
	Entity();
	Entity(TexturedModel* _textured_model, vec3 _position, vec3 _rotation, float _scale);
  ~Entity() {}

	TexturedModel* getTexturedModel() { return textured_model; }
	vec3 getPosition() { return position; }
	vec3 getRotation() { return rotation; }
	float getScale() { return scale; }

	void move(vec3 dxyz);
	void rotate(vec3 dxyz);
};

#endif
