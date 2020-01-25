#include "application.h"

Application::Application()
: window(1280,720, "0 FSP"), camera(&window),
  renderer(70, 1280/720, 0.1f, 100.0f, &static_shader)
{
}

Application::~Application()
{
}

void Application::run()
{
  vector<unsigned int> indices;
	vector<GLfloat> vertices;
	vector<GLfloat> uvs;
	vector<GLfloat> normals;
	bool res = loadAssImp("./res/stall.obj", indices, vertices, uvs, normals);

  RawModel raw_model = loadRawModel(vertices, indices);
  ModelTexture model_texture = loadModelTexture(uvs, "./res/stallTexture.bmp");
  TexturedModel textured_model(&raw_model, &model_texture);
  Entity entity = Entity(&textured_model, vec3(0.0f,0.0f,0.0f), vec3(0.0f,0.0f,0.0f), 1.0f);

  while(!glfwWindowShouldClose(window.getWindow()))
  {
    camera.update();
    fps_counter.update(&window);

    renderer.prepare();
    static_shader.start();
    static_shader.loadViewMatrix(&camera);
    renderer.render(&entity, &static_shader);
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
