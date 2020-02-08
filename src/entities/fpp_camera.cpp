#include "fpp_camera.h"
#include "../config.h"
#include "../terrain/terrain.h"
#include "../window.h"

FPPCamera::FPPCamera(Window *_window)
: pitch(-0.25f), window(_window)
{
}

void FPPCamera::move(Terrain* terrain, float elapsed_time)
{
  double xpos, ypos;
  glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
  glfwSetCursorPos(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);
  yaw += config.mouseSensitivity * elapsed_time * float(window->getWidth() / 2 - xpos);
  pitch += config.mouseSensitivity * elapsed_time * float(window->getHeight() / 2 - ypos);

  pitch = clamp(pitch, -3.14f/2, 3.14f/2);

  vec3 direction(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
  vec3 right(sin(yaw - 3.14f / 2.0f), 0, cos(yaw - 3.14f / 2.0f));

  if(glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
      position += direction * elapsed_time * config.runSpeed;
  }else if(glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
      position -= direction * elapsed_time * config.runSpeed;
  }
  if(glfwGetKey(window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
      position += right * elapsed_time * config.runSpeed;
  }else if(glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
      position -= right * elapsed_time * config.runSpeed;
  }

  if(isFreeCam == false)
  {
    if(glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
      jump();
    }

    upwardsSpeed += config.gravity * elapsed_time;
    position.y += upwardsSpeed * elapsed_time;
    float terrainHeight = terrain->getHeightOfTerrain(position.x, position.z);
    if(position.y < terrainHeight + config.playerHeight)
    {
      upwardsSpeed = 0;
      position.y = terrainHeight + config.playerHeight;
      isInAir = false;
    }
  }
}

void FPPCamera::jump()
{
  if(!isInAir)
  {
    upwardsSpeed = config.jumpPower;
    isInAir = true;
  }
}
