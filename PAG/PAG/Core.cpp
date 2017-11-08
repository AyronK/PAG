#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Core.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp""
#include "Transform.hpp"
#include "Scene.hpp"
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

		Transform center = Transform();
		center.rotate((float)glfwGetTime() * glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.5f));
		center.scale(glm::vec3(2, 2, 2));
		shader->setMat4("model", center.transform);
		texture->setActiveTexture(0);
		mesh->draw();

		Transform planet1 = Transform();
		planet1.rotate((float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.5f));
		planet1.translate(glm::vec3(4.5f, 0.0f, 0.0f));
		planet1.rotate((float)glfwGetTime() * glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader->setMat4("model", planet1.transform);
		texture->setActiveTexture(1);
		mesh->draw();

		Transform planet1Moon = Transform();
		planet1Moon.transform = planet1.transform;
		planet1Moon.rotate((float)glfwGetTime() * glm::radians(-500.0f), glm::vec3(0.0f, 1.0f, 0.5f));
		planet1Moon.translate(glm::vec3(1.5f, 0.0f, 0.0f));
		planet1Moon.rotate((float)glfwGetTime() * glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		shader->setMat4("model", planet1Moon.transform);
		texture->setActiveTexture(1);
		mesh->draw();
		
		Transform planet2 = Transform();
		planet2.rotate((float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.5f));
		planet2.translate(glm::vec3(13.0f, 0.0f, 0.0f));
		planet2.rotate((float)glfwGetTime() * glm::radians(360.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet2.scale(glm::vec3(0.5f, 0.5f, 0.5f));
		shader->setMat4("model", planet2.transform);
		texture->setActiveTexture(1);
		mesh->draw();
		
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
