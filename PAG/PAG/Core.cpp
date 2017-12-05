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
#include "UserInterface.hpp"
using namespace std;

void Core::run()
{
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//Model robocopModel("/Users/sern19/Desktop/Tmp/2B/2B.fbx");
	Model model("F:/Studia/Sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	//model.getRootNode()->getNodeTransform()->rotate(90, glm::vec3(0, 0, 1));
	//model.getRootNode()->getChildren(0)->getChildren(0)->getNodeTransform()->translate(glm::vec3(1, 1, 1));
	//model.getRootNode()->getChildren(0)->getChildren(0)->getChildren(0)->getNodeTransform()->translate(glm::vec3(1, 1, 1));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe

	model.getRootNode()->getNodeTransform()->scale(glm::vec3(0.005, 0.005, 0.005));
	//model.getRootNode()->getNodeTransform()->translate(glm::vec3(-0.5, 0, 0));
	//model.getRootNode()->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getNodeTransform()->scale(glm::vec3(10, 2, 2));

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput();
		processMouse(*scene, &model);

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();

		scene->updateViewSpace(*camera);
		shader->updateScene(*scene);

		model.draw(shader.get());
		ui->draw();
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
	ui = std::make_unique<UserInterface>(window->getWindow());
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

void Core::processMouse(Scene scene, Model* model)
{

	std::pair<double, double> mousePos;
	glfwGetCursorPos(window->getWindow(), &mousePos.first, &mousePos.second);

	if (camera->firstMouse)
	{
		camera->lastX = mousePos.first;
		camera->lastY = mousePos.second;
		camera->firstMouse = false;
	}

	float offsetX = (mousePos.first - camera->lastX) * mouseSensivity;
	float offsetY = (camera->lastY - mousePos.second) * mouseSensivity;

	camera->lastX = mousePos.first;
	camera->lastY = mousePos.second;

	camera->rotateByOffset(offsetX, offsetY);

	std::pair<int, int> screenSize;
	glfwGetWindowSize(window->getWindow(), &screenSize.first, &screenSize.second);

	if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		for each(auto node in model->getAllNodes()) {
			node->setIsSelected(false);
		}
		mousePicker->update(mousePos.first, mousePos.second);
		auto selectedNode = mousePicker->getSelectedNode(&scene, model, screenSize, mousePos);
		ui->setSelectedNode(selectedNode);
		if (selectedNode != nullptr) {
			selectedNode->setIsSelected(true);
		}
	}
}
