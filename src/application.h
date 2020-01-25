#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "./entities/camera.h"
#include "./utilities/fps_counter.h"
#include "./renderer/renderer.h"
#include "./shaders/static_shader.h"
#include "./entities/entity.h"

class Application
{
  Window window;
  Camera camera;
  FpsCounter fps_counter;
  StaticShader static_shader;
  Renderer renderer;

public:
  Application();
  ~Application();

  void run();

private:
  void handleEvents();
};

#endif // APPLICATION_H
