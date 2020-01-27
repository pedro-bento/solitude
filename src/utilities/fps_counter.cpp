#include "fps_counter.h"

FpsCounter::FpsCounter()
: frames(0), acc_time(0)
{
}

FpsCounter::~FpsCounter()
{
}

void FpsCounter::update(Window* window, float elapsed_time)
{
  acc_time += elapsed_time;
  frames++;

  if(acc_time >= 1.0f)
  {
    int fps = float(frames) / acc_time;

    std::string fps_string("SOLITUDE: " + std::to_string(fps) + " FPS");

    glfwSetWindowTitle(window->getWindow(), fps_string.c_str());

    acc_time = 0;
    frames = 0;
  }
}
