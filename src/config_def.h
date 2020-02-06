#ifndef CONFIG_DEF_H
#define CONFIG_DEF_H

#include <glm/glm.hpp>
using namespace glm;

struct Config
{
  // Player
  float FOV = 70.0f;
  float viewDistance = 200.0f;
  float mouseSensitivity = 0.3f;
  float runSpeed = 30.0f;
  float playerHeight = 6.5f;
  float jumpPower = 15;

  // World
  vec3 skyColour = vec3(0.6f, 0.76f, 0.87f);
  float bucketSize = 256;
  float bucketVertexCount = bucketSize/16.0f;
  float bucketMaxHeight = 50.0f;
  float gravity = -40;
};

#endif
