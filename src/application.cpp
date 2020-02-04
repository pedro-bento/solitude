#include "application.h"

Application::Application()
: fpp_camera(&window),
  master_renderer(window.getWidth()/window.getHeight()),
  light(vec3(0.0f,500.0f,200.0f), vec3(1.0f,1.0f,1.0f)),
  backTexture(loadDDS("./res/grassy2.dds")),
  rTexture(loadDDS("./res/mud.dds")),
  gTexture(loadDDS("./res/grassFlowers.dds")),
  bTexture(loadDDS("./res/path.dds")),
  texturePack(&backTexture, &rTexture, &gTexture, &bTexture),
  blendMap(loadDDS("./res/blendMap.dds"))
{
  terrains.push_back(make_unique<Terrain>(0,0,&texturePack, &blendMap));
  terrains.push_back(make_unique<Terrain>(-1,0,&texturePack, &blendMap));
  terrains.push_back(make_unique<Terrain>(0,-1,&texturePack, &blendMap));
  terrains.push_back(make_unique<Terrain>(-1,-1,&texturePack, &blendMap));
  populate();
}

Application::~Application()
{
}

void Application::run()
{
  while(!window.shouldClose())
  {
    window.update();
    fps_counter.update(&window, window.getElapsedTime());
    fpp_camera.move(terrains[0].get(), window.getElapsedTime());

    for(auto& terrain : terrains)
      master_renderer.processTerrain(terrain.get());
    for(auto& entity : entities)
     master_renderer.processEntity(entity.get());

     master_renderer.render(&light, &fpp_camera);

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
  int num_trees = 80;
  int num_poly_trees = 30;
  int num_fern = 300;
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
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    entities.push_back(make_unique<Entity>(tree,vec3(x,terrains[0].get()->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 8.0f));
  }
  for(int i = 0; i < num_poly_trees; i++)
  {
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    entities.push_back(make_unique<Entity>(poly_tree,vec3(x,terrains[0].get()->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.7f));
  }
  for(int i = 0; i < num_fern; i++)
  {
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    int n = Random::randomInt(0,4);
    entities.push_back(make_unique<Entity>(fern,vec3(x,terrains[0].get()->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.4f, n));
  }
  for(int i = 0; i < num_grass; i++)
  {
    float x = Random::randomFloat(20.0f,1000.0f);
    float z = Random::randomFloat(20.0f,1000.0f);
    entities.push_back(make_unique<Entity>(grass,vec3(x,terrains[0].get()->getHeightOfTerrain(x,z),z),vec3(0.0f,0.0f,0.0f), 0.8f));
  }
}
