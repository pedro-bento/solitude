//#include "application.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
using namespace std;

#include "window.h"
#include "./entities/camera.h"
#include "./utilities/fps_counter.h"
#include "./renderer/renderer.h"
#include "./shaders/static_shader.h"
#include "./models/textured_model.h"
#include "./textures/model_texture.h"
#include "./entities/entity.h"
#include "./entities/light.h"
#include "./renderer/master_renderer.h"

const int window_width = 1280;
const int window_height = 720;

int main(void)
{
  //Application app;
  //app.run();

  Window window(window_width,window_height, "SOLITUDE: 0 FSP");
  Camera camera(&window);
  FpsCounter fps_counter;
  StaticShader static_shader;
  vector<unique_ptr<Entity>> entities;
  Light light(vec3(0.0f,500.0f,0.0f), vec3(1.0f,1.0f,1.0f));

  shared_ptr<TexturedModel> t0 = loadTexturedModel(
    "./res/dragon.obj",
    "./res/white.bmp");

  t0->getModelTexture()->setShineDamper(10.0f);
  t0->getModelTexture()->setReflectivity(1.0f);

  entities.push_back(
    make_unique<Entity>(
      t0,
      vec3(0.0f,0.0f,0.0f),
      vec3(0.0f,0.0f,0.0f),
      1.0f));

  shared_ptr<TexturedModel> t = loadTexturedModel(
    "./res/stall.obj",
    "./res/stallTexture.bmp");

  t->getModelTexture()->setShineDamper(10.0f);
  t->getModelTexture()->setReflectivity(1.0f);

   entities.push_back(
     make_unique<Entity>(
       t,
       vec3(30.0f,0.0f,-5.0f),
       vec3(0.0f,90.0f,0.0f),
       1.0f));

  float current_time, elapsed_time;
  float last_time = glfwGetTime();

  MasterRenderer master_renderer(window_width/window_height);

  while(!glfwWindowShouldClose(window.getWindow()))
  {
   current_time = glfwGetTime();
   elapsed_time = current_time - last_time;
   last_time = current_time;

   fps_counter.update(&window, elapsed_time);
   camera.update(elapsed_time);

   for(auto& entity : entities)
   {
     entity->rotate(elapsed_time * vec3(0.0f,15.0f,0.0f));
   }

   for(size_t i = 0; i < entities.size(); i++)
   {
     master_renderer.processEntity(entities[i].get());
   }

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
