#ifndef WINDOW_H
#define WINDOW_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	float current_time = 0;
	float last_time = 0;
	float elapsed_time = 0;
	int width;
	int height;
  GLFWwindow* window;
	const char* title = "SOLITUDE :: 0 FPS\0";

public:
	float getElapsedTime() { return elapsed_time; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	GLFWwindow* getWindow() { return window; }

	void setWidth(int v) { width = v; }
	void setHeight(int v) { height = v; }

	bool shouldClose();
	void update();

	Window();
	~Window();
};

#endif // WINDOW_H
