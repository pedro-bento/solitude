#include "application.h"

Application::Application()
: window(window_width,window_height, "0 FSP"),
  camera(&window),
  renderer(70, window_width/window_height, 0.1f, 100.0f, &static_shader),
  light(vec3(0.0f,250.0f,0.0f),vec3(1.0f,1.0f,1.0f))
{
  entities.push_back(
    make_unique<Entity>
      (loadTexturedModel("./res/dragon.obj",
                         "./res/white.bmp"),
           vec3(0.0f,0.0f,0.0f),
           vec3(0.0f,0.0f,0.0f),
           1.0f));

   entities.push_back(
     make_unique<Entity>
       (loadTexturedModel("./res/stall.obj",
                          "./res/stallTexture.bmp"),
            vec3(30.0f,0.0f,-5.0f),
            vec3(0.0f,90.0f,0.0f),
            1.0f));
}

Application::~Application()
{
}

void Application::run()
{
  float current_time, last_time = glfwGetTime();

  while(!glfwWindowShouldClose(window.getWindow()))
  {
    current_time = glfwGetTime();
    fps_counter.update(&window);
    camera.update(current_time - last_time);
    last_time = current_time;

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
