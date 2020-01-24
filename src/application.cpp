#include "application.h"

vector<GLfloat> vertices{
  -0.5f,0.5f,-0.5f,
  -0.5f,-0.5f,-0.5f,
  0.5f,-0.5f,-0.5f,
  0.5f,0.5f,-0.5f,

  -0.5f,0.5f,0.5f,
  -0.5f,-0.5f,0.5f,
  0.5f,-0.5f,0.5f,
  0.5f,0.5f,0.5f,

  0.5f,0.5f,-0.5f,
  0.5f,-0.5f,-0.5f,
  0.5f,-0.5f,0.5f,
  0.5f,0.5f,0.5f,

  -0.5f,0.5f,-0.5f,
  -0.5f,-0.5f,-0.5f,
  -0.5f,-0.5f,0.5f,
  -0.5f,0.5f,0.5f,

  -0.5f,0.5f,0.5f,
  -0.5f,0.5f,-0.5f,
  0.5f,0.5f,-0.5f,
  0.5f,0.5f,0.5f,

  -0.5f,-0.5f,0.5f,
  -0.5f,-0.5f,-0.5f,
  0.5f,-0.5f,-0.5f,
  0.5f,-0.5f,0.5f
};

vector<unsigned int> indices{
  0,1,3,
	3,1,2,
	4,5,7,
	7,5,6,
	8,9,11,
	11,9,10,
	12,13,15,
	15,13,14,
	16,17,19,
	19,17,18,
	20,21,23,
	23,21,22
};

vector<GLfloat> textureCoords{
  0,0,
	0,1,
	1,1,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0,
	0,0,
	0,1,
	1,1,
	1,0
};

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
  RawModel raw_model = loadRawModel(vertices, indices);
  ModelTexture model_texture = loadModelTexture(textureCoords, "./res/texture.bmp");
  TexturedModel textured_model(&raw_model, &model_texture);
  entity = Entity(&textured_model, vec3(0.0f,0.0f,0.0f), vec3(0.0f,0.0f,0.0f), 1.0f);

  while(!glfwWindowShouldClose(window.getWindow()))
  {
    entity.rotate(vec3(0.01f,0.01f,0.0f));
    camera.move(0.0f);
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
