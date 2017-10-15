#pragma once
#include <GLFW/glfw3.h> //Do tworzenia okna
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
	Window(int width, int height, char*);	
	GLFWwindow* getWindow();
};
