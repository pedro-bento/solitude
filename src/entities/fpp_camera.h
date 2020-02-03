#ifndef CAMERA_H
#define CAMERA_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#include "../window.h"

class FPPCamera
{
	vec3 position = vec3(0.0f,6.5f,0.0f);;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float mouse_speed = 0.3f;
	float speed = 30.0f;
	Window* window;

	const float PLAYER_HEIGHT = 6.5f;
	const float GRAVITY = -100;
  const float JUMP_POWER = 40;
  const float TERRAIN_HEIGHT = 0.0f;
	float upwardsSpeed = 0;
  bool isInAir = false;

public:
	FPPCamera(Window* _window);
  ~FPPCamera() {}

  vec3 getPosition() { return position; }
  float getPitch() { return pitch; }
  float getYaw() { return yaw; }

	void update(float elapsed_time);

private:
	void jump();
};

#endif
