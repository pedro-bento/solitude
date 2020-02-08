#ifndef CONFIG_DEF_H
#define CONFIG_DEF_H

#include <glm/glm.hpp>
using namespace glm;

struct Config
{
  // Player
  float FOV = 70.0f;
  float viewDistance = 1024.0f;
  float mouseSensitivity = 0.3f;
  float runSpeed = 20.0f;
  float playerHeight = 6.5f;
  float jumpPower = 15;

  // World
  vec3 skyColour = vec3(0.5444f, 0.62f, 0.69f);
  float bucketSize = 1024.0f;
  float bucketVertexCount = bucketSize/16.0f;
  float bucketMaxHeight = 80.0f;
  float gravity = -40;
};

#endif
