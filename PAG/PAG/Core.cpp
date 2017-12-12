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

	std::vector<Model*> models;
	Model cubes("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	Model nano("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/nanosuit/source/nanosuit.obj", shader.get());
	//Model lambo("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/Lambo/source/Avent.obj", shader.get());
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe

	cubes.getRootNode()->getNodeTransform()->scale(glm::vec3(0.005, 0.005, 0.005));
	nano.getRootNode()->getNodeTransform()->translate(glm::vec3(1.0f, 0.0f, 0.0f));
	nano.getRootNode()->getNodeTransform()->scale(glm::vec3(0.07, 0.07, 0.07));
	//lambo.getRootNode()->getNodeTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
	nano.getRootNode()->getNodeTransform()->translate(glm::vec3(5.0f, 0.0f, 0.0f));
	
	models.push_back(&cubes);
	models.push_back(&nano);
	//models.push_back(&lambo);

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput();
		processMouse(*scene, models);

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->use();

		scene->updateViewSpace(*camera);
		shader->updateScene(*scene);

		for each (auto model in models)
		{
			model->draw(shader.get());
		}
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
	mousePicker = std::make_unique<MousePicker>();
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

void Core::processMouse(Scene scene, std::vector<Model*> models)
{

	std::pair<double, double> mousePos;
	glfwGetCursorPos(window->getWindow(), &mousePos.first, &mousePos.second);

	if (cameraMove)
	{
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
	}

	std::pair<int, int> screenSize;
	glfwGetWindowSize(window->getWindow(), &screenSize.first, &screenSize.second);

	if (glfwGetKey(window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		cameraMove = !cameraMove;
	}

	if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		for each (auto model in models)
		{
			for each(auto node in model->getAllNodes()) {
				node->setIsSelected(false);
			}
		}
		auto selectedNode = mousePicker->getSelectedNode(&scene, models, screenSize, mousePos);
		ui->setSelectedNode(selectedNode);
		if (selectedNode != nullptr) {
			selectedNode->setIsSelected(true);
		}
	}
}
