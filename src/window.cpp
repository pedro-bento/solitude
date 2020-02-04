#include "window.h"

Window::Window()
: last_time(glfwGetTime())
{
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
	}

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	width = mode->width;
	height = mode->height;

	window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
	if(window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glewExperimental = true;
	GLenum error = glewInit();
	if(error != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW.\n%s\n", glewGetErrorString(error));
		glfwTerminate();
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
  glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::shouldClose()
{
	return (bool)glfwWindowShouldClose(window);
}

void Window::update()
{
	current_time = glfwGetTime();
	elapsed_time = current_time - last_time;
	last_time = current_time;
}
