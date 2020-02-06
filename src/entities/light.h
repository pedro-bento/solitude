#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
using namespace glm;

class Light
{
  vec3 position;
  vec3 colour;
  vec3 attenuation;

public:
  Light(vec3 _position, vec3 _colour, vec3 _attenuation)
  : position(_position), colour(_colour), attenuation(_attenuation) {}

  Light(vec3 _position, vec3 _colour)
  : position(_position), colour(_colour), attenuation(1.0f,0.0f,0.0f) {}
  ~Light() {}

  vec3 getPosition() { return position; }
  vec3 getColour() { return colour; }
  vec3 getAttenuation() { return attenuation; }
};

#endif
