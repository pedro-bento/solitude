#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "../window.h"

#include <cmath>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

class Player : public Entity
{
  const float RUN_SPEED = 20;
  const float TURN_SPEED = 160;
  const float GRAVITY = -50;
  const float JUMP_POWER = 30;
  const float TERRAIN_HEIGHT = 1.0f;

  float currentSpeed = 0;
  float currentTurnSpeed = 0;
  float upwardsSpeed = 0;

  bool isInAir = false;

public:
  Player(shared_ptr<TexturedModel> _textured_model, vec3 _position, vec3 _rotation, float _scale);
  ~Player();

  void move(float elapsed_time, Window* window);

private:
  void jump();
  void checkInputs(Window* window);
};

#endif
