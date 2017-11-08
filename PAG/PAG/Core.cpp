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
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -15.0f),  // camera position in world space
		glm::vec3(0.0f, 0.0f, 0.0f),  // at this point camera is looking
		glm::vec3(0.0f, 1.0f, 0.0f)); // head is up

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		// clear scene
		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader->use();
		glBindVertexArray(mesh->VertexArrayObject);

		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		{
			float angle = 60.0f;
			glm::mat4 model = glm::mat4(1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.5f));
			shader->setMat4("model", model);
			texture->setActiveTexture(0);
			mesh->draw();
		} 
		{
			float angle = 60.0f;
			glm::mat4 parent = glm::mat4(1);
			parent = glm::rotate(parent, (float)glfwGetTime() * glm::radians(100.0f), glm::vec3(0.0f, 1.0f, 0.5f));
			parent = glm::translate(parent, glm::vec3(3.0f, 0.0f, 0.0f));
			parent = glm::rotate(parent, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			{
				float angle = 60.0f;
				glm::mat4 model = parent;
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-500.0f), glm::vec3(0.0f, 1.0f, 0.5f));
				model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
				shader->setMat4("model", model);
				texture->setActiveTexture(1);
				mesh->draw();
			}
			{
				float angle = 60.0f;
				glm::mat4 model = parent;
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(300.0f), glm::vec3(1.0f, 0.0f, 0.5f));
				model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
				shader->setMat4("model", model);
				texture->setActiveTexture(1);
				mesh->draw();
			}
			shader->setMat4("model", parent);
			texture->setActiveTexture(1);
			mesh->draw();
		}
		{
			float angle = 60.0f;
			glm::mat4 model = glm::mat4(1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

			shader->setMat4("model", model);
			texture->setActiveTexture(1);
			mesh->draw();
		}

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
	mesh->loadContent();

	texture = std::make_unique<Texture>();

	shader = std::make_unique<Shader>();

	shader->use();
	shader->setInt("texture", 0);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Core::~Core()
{
}
