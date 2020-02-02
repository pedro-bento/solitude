#include "player.h"

Player::Player(shared_ptr<TexturedModel> _textured_model, vec3 _position, vec3 _rotation, float _scale)
: Entity(_textured_model, _position, _rotation, _scale)
{
}

Player::~Player()
{
}

void Player::move(float elapsed_time, Window* window)
{
  checkInputs(window);
  Entity::rotate(vec3(0.0f, currentTurnSpeed * elapsed_time, 0.0f));

  float distance = currentSpeed * elapsed_time;
  float dx = distance * sin(radians(Entity::getRotation().y));
  float dz = distance * cos(radians(Entity::getRotation().y));

  upwardsSpeed += GRAVITY * elapsed_time;

  Entity::move(vec3(dx, upwardsSpeed * elapsed_time, dz));
  vec3 pos = Entity::getPosition();
  if(pos.y < TERRAIN_HEIGHT)
  {
    upwardsSpeed = 0;
    pos.y = TERRAIN_HEIGHT;
    isInAir = false;
    Entity::setPosition(pos);
  }
}

void Player::jump()
{
  if(!isInAir)
  {
    upwardsSpeed = JUMP_POWER;
    isInAir = true;
  }
}

void Player::checkInputs(Window *window)
{
  if(glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
    currentSpeed = RUN_SPEED;
  }else if(glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
    currentSpeed = -RUN_SPEED;
  }else{
    currentSpeed = 0;
  }

  if(glfwGetKey(window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
    currentTurnSpeed = -TURN_SPEED;
  }else if(glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
    currentTurnSpeed = TURN_SPEED;
  }else{
    currentTurnSpeed = 0;
  }

  if(glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    jump();
  }
}
