#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
using namespace glm;

class Light
{
  vec3 position;
  vec3 colour;

public:
  Light(vec3 _position, vec3 _colour) : position(_position), colour(_colour) {}
  ~Light() {}

  vec3 getPosition() { return position; }
  vec3 getColour() { return colour; }
};

#endif
