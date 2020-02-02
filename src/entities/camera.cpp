#include "camera.h"

Camera::Camera(Window *_window)
: window(_window)
{
}

void Camera::update(float elapsed_time)
{
  double xpos, ypos;
  glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
  glfwSetCursorPos(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);
  yaw += mouse_speed * elapsed_time * float(window->getWidth() / 2 - xpos);
  pitch += mouse_speed * elapsed_time * float(window->getHeight() / 2 - ypos);

  vec3 direction(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
  vec3 right(sin(yaw - 3.14f / 2.0f), 0, cos(yaw - 3.14f / 2.0f));

  if(glfwGetKey(window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
      position += direction * elapsed_time * speed;
  }else if(glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
      position -= direction * elapsed_time * speed;
  }else if(glfwGetKey(window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
      position += right * elapsed_time * speed;
  }else if(glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS
      || glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
      position -= right * elapsed_time * speed;
  }
}
