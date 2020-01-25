#ifndef CAMERA_H
#define CAMERA_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
using namespace std;

#include "../window.h"

class Camera
{
	vec3 position = vec3(0.0f,0.0f,0.0f);;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float mouse_speed = 0.15f;
	float speed = 8.5f;
	Window* window;

public:
	Camera(Window* _window);
  ~Camera() {}

  vec3 getPosition() { return position; }
  float getPitch() { return pitch; }
  float getYaw() { return yaw; }

	void update(float elapsed_time);
};

#endif
