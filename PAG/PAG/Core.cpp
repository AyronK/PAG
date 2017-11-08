#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Core.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp""
#include "Transform.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void Core::run()
{
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		//get time values
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput();
		processMouse();

		glm::mat4 view = glm::lookAt(camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);

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

	camera = std::make_unique<Camera>();
	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Core::~Core()
{
}

void Core::processInput()
{
	if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window->getWindow(), true);

	GLfloat cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		camera->cameraPos += cameraSpeed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		camera->cameraPos -= cameraSpeed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * cameraSpeed;

	/* Jeœli chcemy poruszaæ siê do przodu lub do ty³u, dodajemy lub odejmujemy
	wektor kierunku od wektora po³o¿enia.Jeœli chcemy przesuwaæ siê na boki,
	wykonujemy iloczyn wektorowy, aby utworzyæ prawy wektor i odpowiednio
	poruszaæ siê wzd³u¿ tego wektora w prawo. */
}

void Core::processMouse()
{

	double mousePosX, mousePosY;
	glfwGetCursorPos(window->getWindow(), &mousePosX, &mousePosY);

	if (camera->firstMouse)
	{
		camera->lastX = mousePosX;
		camera->lastY = mousePosY;
		camera->firstMouse = false;
	}

	float offsetX = (mousePosX - camera->lastX) * mouseSensivity;
	float offsetY = (camera->lastY - mousePosY) * mouseSensivity; // Odwrócone, poniewa¿ wspó³rzêdne y zmieniaj¹ siê od do³u do góry

	camera->lastX = mousePosX;
	camera->lastY = mousePosY;

	camera->rotateByOffset(offsetX, offsetY);
}
