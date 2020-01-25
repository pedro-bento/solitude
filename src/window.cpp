#include "window.h"

Window::Window(int _width, int _height, const char* _title)
{
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	width = _width;
	height = _height;
	title = _title;

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if(window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	GLenum error = glewInit();
	if(error != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW.\n%s\n", glewGetErrorString(error));
		glfwTerminate();
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

Window::~Window()
{
  glfwDestroyWindow(window);
	glfwTerminate();
}
