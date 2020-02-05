#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
using namespace std;

#include "window.h"
#include "./entities/fpp_camera.h"
#include "./utilities/fps_counter.h"
#include "./shaders/static_shader.h"
#include "./models/textured_model.h"
#include "./textures/model_texture.h"
#include "./textures/terrain_texture.h"
#include "./textures/terrain_texture_pack.h"
#include "./entities/entity.h"
#include "./entities/light.h"
#include "./renderer/master_renderer.h"
#include "./terrain/terrain_master.h"
#include "./terrain/terrain.h"
#include "./entities/player.h"
#include "./utilities/maths.h"
#include "./guis/gui_texture.h"
#include "./guis/gui_renderer.h"

class Application
{
  Window window;
  FPPCamera fpp_camera;
  FpsCounter fps_counter;
  StaticShader static_shader;
  MasterRenderer master_renderer;
  Light light1;
  Light light2;
  Light light3;
  TerrainMaster terrain_master;

  vector<unique_ptr<Entity>> entities;

public:
  Application();
  ~Application();

  void run();

private:
  void handleEvents();

  // change
  void populate();
};

#endif // APPLICATION_H
