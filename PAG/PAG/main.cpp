#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

int main()
{
	try {
		Core core;
		core.run();
	}
	catch (std::exception e) {
		std::cout << e.what()<<std::endl;
		std::system("PAUSE");
		return -1;
	}
	return 0;
}