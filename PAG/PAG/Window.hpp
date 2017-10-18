#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "const.hpp"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// -------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window
{
private:
	GLFWwindow *window;	
public:
	Window();
	~Window();
	Window(int width, int height, char*);	
	GLFWwindow* getWindow();
};
