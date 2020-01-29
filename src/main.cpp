//#include "application.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
using namespace std;

#include "window.h"
#include "./entities/camera.h"
#include "./utilities/fps_counter.h"
#include "./shaders/static_shader.h"
#include "./models/textured_model.h"
#include "./textures/model_texture.h"
#include "./entities/entity.h"
#include "./entities/light.h"
#include "./renderer/master_renderer.h"

#include "./terrain/terrain.h"

#include <cstdlib>

const int window_width = 1280;
const int window_height = 720;

float randFloat(float min, float max)
{
  float f = (float)rand() / RAND_MAX;
  return min + f * (max - min);
}

// TODO: MasterRenderer should store value of TextureModel

int main(void)
{
  //Application app;
  //app.run();

  Window window(window_width,window_height, "SOLITUDE: 0 FSP");
  Camera camera(&window);
  FpsCounter fps_counter;
  StaticShader static_shader;

  Light light(vec3(0.0f,500.0f,0.0f), vec3(1.0f,1.0f,1.0f));

  int num_trees = 1000;

  vector<Entity*> entities;
  entities.resize(num_trees);

  entities[0] = new Entity(
    loadTexturedModel("./res/tree.obj","./res/tree.bmp"),
    vec3(0.0f,0.0f,10.0f),vec3(0.0f,0.0f,0.0f),1.0f);

  for(int i = 0; i < num_trees; i++)
  {
    entities[i] = new Entity(entities[0]->getTexturedModel(),
      vec3(
        randFloat(-100.0f,100.0f),
        0.0f,
        randFloat(-100.0f,100.0f)),
      vec3(0.0f,0.0f,0.0f), 1.0f);
  }

  Terrain terrain1(0,0,loadModelTexture("./res/grass.bmp"));
  Terrain terrain2(-1,0,terrain1.getModelTexture());
  Terrain terrain3(0,-1,terrain1.getModelTexture());
  Terrain terrain4(-1,-1,terrain1.getModelTexture());

  MasterRenderer master_renderer(window_width/window_height);

  float current_time, elapsed_time;
  float last_time = glfwGetTime();

  cout << entities.size() << endl;

  while(!glfwWindowShouldClose(window.getWindow()))
  {
   current_time = glfwGetTime();
   elapsed_time = current_time - last_time;
   last_time = current_time;

   fps_counter.update(&window, elapsed_time);
   camera.update(elapsed_time);

   for(auto entity : entities)
   {
     master_renderer.processEntity(entity);
   }

   master_renderer.processTerrain(&terrain1);
   master_renderer.processTerrain(&terrain2);
   master_renderer.processTerrain(&terrain3);
   master_renderer.processTerrain(&terrain4);

   master_renderer.render(&light, &camera);

   glfwSwapBuffers(window.getWindow());
   glfwPollEvents();
   if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window.getWindow(), GLFW_TRUE);
   }

  }

  return 0;
}
