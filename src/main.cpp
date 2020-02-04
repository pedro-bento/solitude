//#include "application.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
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
#include "./terrain/terrain.h"
#include "./entities/player.h"

void populate(Terrain* terrain, vector<unique_ptr<Entity>>& entities,
  int num_trees, int num_poly_trees, int num_fern, int num_grass)
{
  shared_ptr<TexturedModel> tree = loadTexturedModel("./res/tree.obj","./res/tree.dds");
  shared_ptr<TexturedModel> poly_tree = loadTexturedModel("./res/lowPolyTree.obj","./res/lowPolyTree.dds");
  shared_ptr<TexturedModel> fern = loadTexturedModel("./res/fern.obj","./res/fern.dds");
  shared_ptr<TexturedModel> grass = loadTexturedModel("./res/grassModel.obj","./res/grassTexture.dds");
  grass->getModelTexture()->setHasTransparency(true);
  grass->getModelTexture()->setUseFakeLighting(true);

  for(int i = 0; i < num_trees; i++)
  {
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    entities.push_back(make_unique<Entity>(tree,vec3(x,terrain->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 8.0f));
  }
  for(int i = 0; i < num_poly_trees; i++)
  {
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    entities.push_back(make_unique<Entity>(poly_tree,vec3(x,terrain->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.7f));
  }
  for(int i = 0; i < num_fern; i++)
  {
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    entities.push_back(make_unique<Entity>(fern,vec3(x,terrain->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.4f));
  }
  for(int i = 0; i < num_grass; i++)
  {
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    entities.push_back(make_unique<Entity>(grass,vec3(x,terrain->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.8f));
  }
}

// TODO: implement 3rd person!!!

int main(void)
{
  const int window_width = 1280;
  const int window_height = 720;

  //Application app;
  //app.run();

  Window window(window_width,window_height, "SOLITUDE: 0 FSP");
  FPPCamera fpp_camera(&window);
  FpsCounter fps_counter;
  StaticShader static_shader;
  MasterRenderer master_renderer(window_width/window_height);
  Light light(vec3(0.0f,500.0f,100.0f), vec3(1.0f,1.0f,1.0f));

  TerrainTexture backTexture(loadDDS("./res/grass.dds"));
  TerrainTexture rTexture(loadDDS("./res/mud.dds"));
  TerrainTexture gTexture(loadDDS("./res/grassFlowers.dds"));
  TerrainTexture bTexture(loadDDS("./res/path.dds"));
  TerrainTexturePack texturePack(&backTexture, &rTexture, &gTexture, &bTexture);
  TerrainTexture blendMap(loadDDS("./res/blendMap.dds"));
  Terrain terrain1(0,0,&texturePack,&blendMap);
  //Terrain terrain2(-1,0,&texturePack,&blendMap);
  //Terrain terrain3(0,-1,&texturePack,&blendMap);
  //Terrain terrain4(-1,-1,&texturePack,&blendMap);

  vector<unique_ptr<Entity>> entities;
  populate(&terrain1, entities, 150, 80, 1500, 0);

  float current_time, elapsed_time;
  float last_time = glfwGetTime();

  //glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while(!glfwWindowShouldClose(window.getWindow()))
  {
   current_time = glfwGetTime();
   elapsed_time = current_time - last_time;
   last_time = current_time;

   fps_counter.update(&window, elapsed_time);
   fpp_camera.move(&terrain1, elapsed_time);

   master_renderer.processTerrain(&terrain1);
   for(auto& entity : entities)
   {
     master_renderer.processEntity(entity.get());
   }

   master_renderer.render(&light, &fpp_camera);

   glfwSwapBuffers(window.getWindow());
   glfwPollEvents();
   if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window.getWindow(), GLFW_TRUE);
   }
  }

  return 0;
}
