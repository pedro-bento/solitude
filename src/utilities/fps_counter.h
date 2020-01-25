#ifndef FPS_CONUTER_H
#define FPS_CONUTER_H

#include "../window.h"
#include <GLFW/glfw3.h>
#include <string>

class FpsCounter
{
  int frames;
  float last_time;

public:
  FpsCounter();
  ~FpsCounter();

  void update(Window* window);
};

#endif // FPS_CONUTER_H
