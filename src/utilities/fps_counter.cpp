#include "fps_counter.h"

FpsCounter::FpsCounter()
: frames(0)
{
  glfwSetTime(0.0f);
}

FpsCounter::~FpsCounter()
{
}

void FpsCounter::update(Window* window)
{
  double elapsedTime = glfwGetTime();
  frames++;

  if(elapsedTime >= 1.0)
  {
    int fps = double(frames) / elapsedTime;

    std::string fps_string(std::to_string(fps) + " FPS");

    glfwSetWindowTitle(window->getWindow(), fps_string.c_str());

    glfwSetTime(0.0f);
    frames = 0;
  }
}
