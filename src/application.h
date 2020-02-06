#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
using namespace std;

#include "window.h"
#include "./utilities/fps_counter.h"
#include "./world/world.h"

class Application
{
  Window window;
  FpsCounter fps_counter;
  World world;

public:
  Application();
  ~Application();

  void run();

private:
  void handleEvents();
};

#endif // APPLICATION_H
