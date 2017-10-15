#pragma once
#include <GLFW/glfw3.h> //Do tworzenia okna
#include "const.hpp"
class Window
{
private:
	GLFWwindow *window;
public:
	Window();
	Window(int width, int height, char*);
	GLFWwindow* getWindow();
};
