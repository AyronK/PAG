#include "Core.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <exception>
#include <stdexcept>

void Core::run()
{
	double nextGameTick = glfwGetTime();
	int loops;

	while (true)
	{
		//Update gry
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT); //Czyszczenie sceny
		//texture->selectActiveTexture(ACTIVE_TEXTURE_FOR_PROGRAM);
		//mesh->drawContent();
		//glfwSwapBuffers(window->getWindow()); //Swap front- i backbuffer
		//glfwPollEvents(); //Poll dla eventów

	}
}

Core::Core()
{
	if (!glfwInit())
		throw std::exception("Cannot initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = new Window();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Cannot initialize GLAD");

	mesh = new Mesh();
	//shader = new Shader();
	//texture = new Texture();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Core::~Core()
{
	if (window)
	{
		delete window;
	}
	if (mesh)
	{
		delete mesh;
	}
	if (texture)
	{
		delete texture;
	}
	if (shader)
	{
		delete shader;
	}
}
