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
#include <vector>
#include "Model.hpp"
#include "MousePicker.hpp"
#include <iostream>
#include "Node.hpp"
using namespace std;

void Core::run()
{
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//Model robocopModel("/Users/sern19/Desktop/Tmp/2B/2B.fbx");
	Model model("F:/Studia/Sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	//model.getRootNode()->getNodeTransform()->rotate(90, glm::vec3(0, 0, 1));
	model.getRootNode()->getNodeTransform()->scale(glm::vec3(0.005, 0.005, 0.005));
	model.getRootNode()->getNodeTransform()->translate(glm::vec3(-0.5, 0, 0));
	//model.getRootNode()->getChildren(0)->getNodeTransform()->translate(glm::vec3(1,1,1));
	//model.getRootNode()->getChildren(0)->getChildren(0)->getNodeTransform()->translate(glm::vec3(1, 1, 1));
	//model.getRootNode()->getChildren(0)->getChildren(0)->getChildren(0)->getNodeTransform()->translate(glm::vec3(1, 1, 1));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput();
		processMouse(*scene);

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader->use();

		scene->updateViewSpace(*camera);
		shader->updateScene(*scene);		

		model.draw(shader.get());

		Transform robocop = Transform();
		robocop.translate(glm::vec3(0.0f, -1.75f, 0.0f));
		robocop.scale(glm::vec3(0.2f, 0.2f, 0.2f));
		shader->setMat4("model", robocop.getTransform());
		//robocopModel.Draw(*shader);

		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}



Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Fix na MacOS
#endif
    
	window = std::make_unique<Window>();

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");

	glEnable(GL_DEPTH_TEST);


	shader = std::make_unique<Shader>();

	shader->use();

	camera = std::make_unique<Camera>();
	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	scene = std::make_unique<Scene>();
	mousePicker = std::make_unique<MousePicker>(*camera, scene->getProjectionSpace());
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

void Core::processMouse(Scene scene)
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

	mousePicker->update(mousePosX, mousePosY);
}
