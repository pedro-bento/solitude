#include "application.h"

Application::Application()
: world(&window)
{
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

    world.update();
    world.render();

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
  shared_ptr<TexturedModel> tree = loadTexturedModel("./res/tree.obj","./res/tree.dds");
  shared_ptr<TexturedModel> poly_tree = loadTexturedModel("./res/lowPolyTree.obj","./res/lowPolyTree.dds");
  shared_ptr<TexturedModel> fern = loadTexturedModel("./res/fern.obj","./res/fern.dds");
  fern->getModelTexture()->setNumberOfRows(2);
  shared_ptr<TexturedModel> grass = loadTexturedModel("./res/grassModel.obj","./res/grassTexture.dds");
  grass->getModelTexture()->setHasTransparency(true);
  grass->getModelTexture()->setUseFakeLighting(true);
}
