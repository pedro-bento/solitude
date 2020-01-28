#include "application.h"
/*
Application::Application()
: window(window_width,window_height, "SOLITUDE: 0 FSP"),
  camera(&window),
  renderer(70, window_width/window_height, 0.1f, 100.0f, &static_shader),
  light(vec3(0.0f,500.0f,0.0f), vec3(1.0f,1.0f,1.0f))
{
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
}

Application::~Application()
{
}

void Application::run()
{
  float current_time, elapsed_time;
  float last_time = glfwGetTime();

  while(!glfwWindowShouldClose(window.getWindow()))
  {
    current_time = glfwGetTime();
    elapsed_time = current_time - last_time;
    last_time = current_time;

    fps_counter.update(&window, elapsed_time);
    camera.update(elapsed_time);

    for(auto& entity : entities)
      entity->rotate(elapsed_time * vec3(0.0f,15.0f,0.0f));

    renderer.prepare();
    static_shader.start();
    static_shader.loadLight(&light);
    static_shader.loadViewMatrix(&camera);
    for(auto& entity : entities)
      renderer.render(entity, &static_shader);
    static_shader.stop();

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
}
*/
