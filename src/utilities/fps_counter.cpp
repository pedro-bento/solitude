#include "fps_counter.h"

FpsCounter::FpsCounter()
: frames(0), last_time(glfwGetTime())
{
}

FpsCounter::~FpsCounter()
{
}

void FpsCounter::update(Window* window)
{
  float current_time = glfwGetTime();
  float elapsed_time = current_time - last_time;
  frames++;

  if(elapsed_time >= 2.0)
  {
    int fps = float(frames) / elapsed_time;

    std::string fps_string(std::to_string(fps) + " FPS");

    glfwSetWindowTitle(window->getWindow(), fps_string.c_str());

    last_time = current_time;
    frames = 0;
  }
}
