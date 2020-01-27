#ifndef FPS_CONUTER_H
#define FPS_CONUTER_H

#include "../window.h"
#include <GLFW/glfw3.h>
#include <string>

class FpsCounter
{
  int frames;
  float acc_time;

public:
  FpsCounter();
  ~FpsCounter();

  void update(Window* window, float elapsed_time);
};

#endif // FPS_CONUTER_H
