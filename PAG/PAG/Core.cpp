#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Core.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <stdexcept>

using namespace std;

void Core::run()
{
	glUniform1i(glGetUniformLocation(shader->getProgram(), "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(shader->getProgram(), "ourTexture2"), 1);
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		// clear scene
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		mesh->draw();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}	
}



Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");
	
	window = std::make_unique<Window>();

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");
	glEnable(GL_DEPTH_TEST);
	mesh = std::make_unique<Mesh>();
	shader = std::make_unique<Shader>();
	glUseProgram(shader->getProgram()); 
	mesh->loadContent();
	

	/* Set world matrix to identity matrix */
	glm::mat4 world = glm::mat4(1.0f);
	/* Set view matrix */
	glm::mat4 view = glm::lookAt(glm::vec3(1.5f, 0.0f, 1.5f),  // camera position in world space
		glm::vec3(0.0f, 0.0f, 0.0f),  // at this point camera is looking
		glm::vec3(0.0f, 1.0f, 0.0f)); // head is up
									  /* Set projection matrix */


									  /* Set MVP matrix */
	glm::mat4 projection = glm::perspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.001f, 50.0f);
	glm::mat4 WVP = projection * view * world;
	/* Get uniform location and send MVP matrix there */
	GLuint wvpLoc = glGetUniformLocation(shader->getProgram(), "wvp");
	glUniformMatrix4fv(wvpLoc, 1, GL_FALSE, &WVP[0][0]);

	texture = std::make_unique<Texture>();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Core::~Core()
{
}
