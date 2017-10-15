#include "Window.hpp"



Window::Window() : Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Window") {}

Window::Window(int width, int height, char* name)
{
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}
}

GLFWwindow * Window::getWindow()
{
	return window;
}
