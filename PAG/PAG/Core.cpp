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

	Transform center = Transform();
	Transform planet1 = Transform();
	Transform planet1Moon = Transform();
	Transform planet1Moon2 = Transform();
	Transform planet1Moon3 = Transform();

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput();
		processMouse();

		glm::mat4 view = glm::lookAt(camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);





		//glm::mat4 x = glm::cross(cameraPos, cameraFront, cameraUp);

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();
		glBindVertexArray(mesh->VertexArrayObject);
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);

		//center.rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//center.scale(glm::vec3(3, 3, 3));
		//shader->setMat4("model", center.transform);
		//texture->setActiveTexture(2);


		//Transform center2 = Transform();
		//center2.transform = center.transform;
		//center2.rotate(glm::radians(1000.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//center2.translate(glm::vec3(0.25f, 0.0f, 0.0f));
		////center2.rotate(glm::radians(10.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		//center2.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		//shader->setMat4("model", center2.transform);
		//texture->setActiveTexture(2);
		//mesh->draw();

		//Transform center3 = Transform();
		//center3.transform = center.transform;
		//center3.rotate(glm::radians(1000.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//center3.translate(glm::vec3(-0.25f, 0.0f, 0.0f));
		////center3.rotate(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//center3.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		//shader->setMat4("model", center3.transform);
		//texture->setActiveTexture(2);
		//mesh->draw();

		planet1.setParent(center);
		planet1.setTransform(center.getTransform());
		planet1.translate(glm::vec3(2.0f, 0.0f, 0.0f));
		planet1.rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1.scale(glm::vec3(0.5, 0.5, 0.5));
		shader->setMat4("model", planet1.getTransform());
		texture->setActiveTexture(1);
		mesh->draw();

		planet1Moon.setParent(planet1);
		planet1Moon.setTransform(planet1.getTransform());
		planet1Moon.rotate(glm::radians(-500.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon.translate(glm::vec3(1.5f, 0.0f, 0.0f));
		planet1Moon.rotate(glm::radians(-60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon.scale(glm::vec3(0.25f, 0.25f, 0.25f));
		shader->setMat4("model", planet1Moon.getTransform());
		texture->setActiveTexture(2);
		mesh->draw();

		planet1Moon2.setParent(planet1);
		planet1Moon2.setTransform(planet1.getTransform());
		planet1Moon2.rotate(glm::radians(-115.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon2.translate(glm::vec3(1.0f, 0.0f, 0.0f));
		planet1Moon2.rotate(glm::radians(-300.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon2.scale(glm::vec3(0.15f, 0.15f, 0.15f));
		shader->setMat4("model", planet1Moon2.getTransform());
		texture->setActiveTexture(1);
		mesh->draw();

		planet1Moon3.setParent(planet1);
		planet1Moon3.setTransform(planet1.getTransform());
		planet1Moon3.rotate(glm::radians(250.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon3.translate(glm::vec3(1.5f, 0.0f, 2.0f));
		planet1Moon3.rotate(glm::radians(-35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		planet1Moon3.scale(glm::vec3(0.2f, 0.2f, 0.2f));
		shader->setMat4("model", planet1Moon3.getTransform());
		texture->setActiveTexture(1);
		mesh->draw();

		//Transform planet2 = Transform();
		//planet2.transform = center.transform;
		//planet2.rotate(glm::radians(200.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet2.translate(glm::vec3(3.0f, 0.0f, 0.0f));
		////planet2.rotate(glm::radians(360.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet2.scale(glm::vec3(0.5f, 0.5f, 0.5f));
		//shader->setMat4("model", planet2.transform);
		//texture->setActiveTexture(0);
		//mesh->draw();

		//Transform planet3= Transform();
		//planet3.transform = center.transform;
		//planet3.rotate(glm::radians(-150.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet3.translate(glm::vec3(2.5f, 0.0f, 0.0f));
		////planet3.rotate(glm::radians(700.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//planet3.scale(glm::vec3(0.75f, 0.75f, 0.75f));
		//shader->setMat4("model", planet3.transform);
		//texture->setActiveTexture(0);
		//mesh->draw();

		//Transform planet3Moon = Transform();
		//planet3Moon.transform = planet3.transform;
		//planet3Moon.rotate(glm::radians(-115.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet3Moon.translate(glm::vec3(1.0f, 0.0f, 0.0f));
		////planet3Moon.rotate(glm::radians(-300.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet3Moon.scale(glm::vec3(0.15f, 0.15f, 0.15f));
		//shader->setMat4("model", planet3Moon.transform);
		//texture->setActiveTexture(1);
		//mesh->draw();




		//Transform planet3Moon2 = Transform();
		//planet3Moon2.transform = planet3.transform;
		//planet3Moon2.rotate(glm::radians(250.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//planet3Moon2.translate(glm::vec3(1.5f, 0.0f, 0.0f));
		////planet3Moon2.rotate(glm::radians(-35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//
		//planet3Moon2.scale((float)glm::cos(glfwGetTime()) * glm::vec3(1.0, 1.0, 1.0));
		//shader->setMat4("model", planet3Moon2.transform);
		//texture->setActiveTexture(1);
		//mesh->draw();

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

	GLfloat speed = deltaTime * cameraSpeed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		camera->cameraPos += speed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		camera->cameraPos -= speed * camera->cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		camera->cameraPos -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		camera->cameraPos += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUp)) * speed;
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
	float offsetY = (camera->lastY - mousePosY) * mouseSensivity;

	camera->lastX = mousePosX;
	camera->lastY = mousePosY;

	camera->rotateByOffset(offsetX, offsetY);
}
