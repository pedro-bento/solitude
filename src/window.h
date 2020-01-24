#ifndef WINDOW_H
#define WINDOW_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	int width;
	int height;
  GLFWwindow* window;
	const char* title;

public:
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	GLFWwindow* getWindow(){ return window; }

	Window(int _width, int _height, const char* _title);
	~Window();
};

#endif // WINDOW_H
