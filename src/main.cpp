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
#include "./textures/terrain_texture.h"
#include "./textures/terrain_texture_pack.h"
#include "./entities/entity.h"
#include "./entities/light.h"
#include "./renderer/master_renderer.h"
#include "./terrain/terrain.h"

#include <cstdlib>

float randFloat(float min, float max)
{
  float f = (float)rand() / RAND_MAX;
  return min + f * (max - min);
}

void populate(vector<unique_ptr<Entity>>& entities,
  int num_trees, int num_poly_trees, int num_fern, int num_grass)
{
  shared_ptr<TexturedModel> tree = loadTexturedModel("./res/tree.obj","./res/tree.dds");
  shared_ptr<TexturedModel> poly_tree = loadTexturedModel("./res/lowPolyTree.obj","./res/lowPolyTree.dds");
  shared_ptr<TexturedModel> fern = loadTexturedModel("./res/fern.obj","./res/fern.dds");
  shared_ptr<TexturedModel> grass = loadTexturedModel("./res/grassModel.obj","./res/grassTexture.dds");
  grass->getModelTexture()->setHasTransparency(true);
  grass->getModelTexture()->setUseFakeLighting(true);

  for(int i = 0; i < num_trees; i++)
    entities.push_back(make_unique<Entity>(tree,vec3(randFloat(20.0f,780.0f),0.0f,randFloat(20.0f,780.0f)),vec3(0.0f,0.0f,0.0f), 4.0f));
  for(int i = 0; i < num_poly_trees; i++)
    entities.push_back(make_unique<Entity>(poly_tree,vec3(randFloat(20.0f,780.0f),0.0f,randFloat(20.0f,780.0f)),vec3(0.0f,0.0f,0.0f), 0.3f));
  for(int i = 0; i < num_fern; i++)
    entities.push_back(make_unique<Entity>(fern,vec3(randFloat(20.0f,780.0f),0.0f,randFloat(20.0f,780.0f)),vec3(0.0f,0.0f,0.0f), 0.5f));
  for(int i = 0; i < num_grass; i++)
    entities.push_back(make_unique<Entity>(grass,vec3(randFloat(20.0f,780.0f),1.2f,randFloat(20.0f,780.0f)),vec3(180.0f,0.0f,0.0f), 1.0f));
}

int main(void)
{
  const int window_width = 1280;
  const int window_height = 720;

  //Application app;
  //app.run();

  Window window(window_width,window_height, "SOLITUDE: 0 FSP");
  Camera camera(&window);
  FpsCounter fps_counter;
  StaticShader static_shader;

  Light light(vec3(0.0f,200.0f,50.0f), vec3(1.0f,1.0f,1.0f));

  int num_trees = 250;
  int num_poly_trees = 100;
  int num_fern = 1000;
  int num_grass = 1000;
  vector<unique_ptr<Entity>> entities;
  populate(entities, num_trees, num_poly_trees, num_fern, num_grass);

  TerrainTexture backTexture(loadDDS("./res/grassy2.dds"));
  TerrainTexture rTexture(loadDDS("./res/mud.dds"));
  TerrainTexture gTexture(loadDDS("./res/grassFlowers.dds"));
  TerrainTexture bTexture(loadDDS("./res/path.dds"));
  TerrainTexturePack texturePack(&backTexture, &rTexture, &gTexture, &bTexture);

  TerrainTexture blendMap(loadDDS("./res/blendMap.dds"));

  Terrain terrain1(0,0,&texturePack,&blendMap);
  Terrain terrain2(-1,0,&texturePack,&blendMap);
  //Terrain terrain3(0,-1,&texturePack,&blendMap);
  //Terrain terrain4(-1,-1,&texturePack,&blendMap);

  MasterRenderer master_renderer(window_width/window_height);

  float current_time, elapsed_time;
  float last_time = glfwGetTime();

  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while(!glfwWindowShouldClose(window.getWindow()))
  {
   current_time = glfwGetTime();
   elapsed_time = current_time - last_time;
   last_time = current_time;

   fps_counter.update(&window, elapsed_time);
   camera.update(elapsed_time);

   for(auto& entity : entities)
   {
     master_renderer.processEntity(entity.get());
   }

   master_renderer.processTerrain(&terrain1);
   master_renderer.processTerrain(&terrain2);
   //master_renderer.processTerrain(&terrain3);
   //master_renderer.processTerrain(&terrain4);

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
