#include "application.h"

Application::Application()
: fpp_camera(&window),
  master_renderer(window.getWidth()/window.getHeight()),
  light1(vec3(0.0f,10000.0f,-7000.0f), vec3(1.0f,1.0f,1.0f)),
  light2(vec3(-200.0f,10.0f,-200.0f), vec3(10.0f,0.0f,0.0f)),
  light3(vec3(200.0f,10.0f,200.0f), vec3(0.0f,0.0f,10.0f))
{
  populate();
}

Application::~Application()
{
}

void Application::run()
{
  GuiTexture gui1(loadDDS("./res/health.dds"), vec2(-0.8f, 0.9f), vec2(0.2f, 0.2f));
  vector<GuiTexture*> guis;
  guis.push_back(&gui1);
  GuiRenderer gui_renderer;

  vector<Light*> lights;
  lights.push_back(&light1);
  lights.push_back(&light2);
  lights.push_back(&light3);

  while(!window.shouldClose())
  {
    window.update();
    fps_counter.update(&window, window.getElapsedTime());
    fpp_camera.move(terrain_master.getTerrain(fpp_camera.getPosition().x,
      fpp_camera.getPosition().z),window.getElapsedTime());

    master_renderer.processTerrain(terrain_master.getTerrain(0,0));
    master_renderer.processTerrain(terrain_master.getTerrain(-1,0));
    master_renderer.processTerrain(terrain_master.getTerrain(0,-1));
    master_renderer.processTerrain(terrain_master.getTerrain(-1,-1));
    for(auto& entity : entities)
     master_renderer.processEntity(entity.get());

     master_renderer.render(lights, &fpp_camera);

     gui_renderer.render(guis);

     glfwSwapBuffers(window.getWindow());
     handleEvents();
  }
}

void Application::handleEvents()
{
  glfwPollEvents();

  if(glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
     glfwSetWindowShouldClose(window.getWindow(), GLFW_TRUE);
  }

  if(glfwGetKey(window.getWindow(), GLFW_KEY_M) == GLFW_PRESS)
  {
     glfwSetWindowMonitor(window.getWindow(), NULL, 320, 180, 1280, 720, 75);
     window.setWidth(1280);
     window.setHeight(720);
  }
}

void Application::populate()
{
  float a = -1000.0f;
  float b = 1000.0f;

  int num_trees = 600;
  int num_poly_trees = 200;
  int num_fern = 0;
  int num_grass = 0;

  shared_ptr<TexturedModel> tree = loadTexturedModel("./res/tree.obj","./res/tree.dds");
  shared_ptr<TexturedModel> poly_tree = loadTexturedModel("./res/lowPolyTree.obj","./res/lowPolyTree.dds");
  shared_ptr<TexturedModel> fern = loadTexturedModel("./res/fern.obj","./res/fern.dds");
  fern->getModelTexture()->setNumberOfRows(2);
  shared_ptr<TexturedModel> grass = loadTexturedModel("./res/grassModel.obj","./res/grassTexture.dds");
  grass->getModelTexture()->setHasTransparency(true);
  grass->getModelTexture()->setUseFakeLighting(true);

  for(int i = 0; i < num_trees; i++)
  {
    float x = Random::randomFloat(a,b);
    float z = Random::randomFloat(a,b);
    entities.push_back(make_unique<Entity>(tree,vec3(x,terrain_master.getTerrain((int)x,(int)z)->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 15.0f));
  }
  for(int i = 0; i < num_poly_trees; i++)
  {
    float x = Random::randomFloat(a,b);
    float z = Random::randomFloat(a,b);
    entities.push_back(make_unique<Entity>(poly_tree,vec3(x,terrain_master.getTerrain((int)x,(int)z)->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 1.5f));
  }
  for(int i = 0; i < num_fern; i++)
  {
    float x = Random::randomFloat(a,b);
    float z = Random::randomFloat(a,b);
    int n = Random::randomInt(0,4);
    entities.push_back(make_unique<Entity>(fern,vec3(x,terrain_master.getTerrain((int)x,(int)z)->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.4f, n));
  }
  for(int i = 0; i < num_grass; i++)
  {
    float x = Random::randomFloat(a,b);
    float z = Random::randomFloat(a,b);
    entities.push_back(make_unique<Entity>(grass,vec3(x,terrain_master.getTerrain((int)x,(int)z)->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.8f));
  }
}
