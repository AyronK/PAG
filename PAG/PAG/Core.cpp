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

	//Model robocopModel("/Users/sern19/Desktop/Tmp/2B/2B.fbx");
	std::vector<Model*> models;
	/*Model cubes("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	Model twoB("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/2B/source/2B.fbx", shader.get());
	Model lambo("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/Lambo/source/Avent.obj", shader.get());*/
	Model cubes("C:/Users/BeataPC/source/repos/PAG/PAG/Objects/Cubes/source/Cubes.fbx", shader.get());
	//Model twoB("C:/Users/BeataPC/source/repos/PAG/PAG/Objects/2B/source/2B.fbx", shader.get());
	//Model lambo("C:/Users/BeataPC/source/repos/PAG/PAG/Objects/Lambo/source/Avent.obj", shader.get());
	Model plane("C:/Users/BeataPC/source/repos/PAG/PAG/Objects/Plane/source/plane.FBX", shader.get());
	
	//model.getRootNode()->getNodeTransform()->rotate(90, glm::vec3(0, 0, 1));
	//model.getRootNode()->getChildren(0)->getChildren(0)->getNodeTransform()->translate(glm::vec3(1, 1, 1));
	//model.getRootNode()->getChildren(0)->getChildren(0)->getChildren(0)->getNodeTransform()->translate(glm::vec3(1, 1, 1));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe

	cubes.getRootNode()->getNodeTransform()->scale(glm::vec3(0.005, 0.005, 0.005));
	//twoB.getRootNode()->getNodeTransform()->translate(glm::vec3(1.0f, 0.0f, 0.0f));
	//twoB.getRootNode()->getNodeTransform()->scale(glm::vec3(0.007, 0.007, 0.007));
	//lambo.getRootNode()->getNodeTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
	//lambo.getRootNode()->getNodeTransform()->translate(glm::vec3(-5.0f, 0.0f, 0.0f));
	//model.getRootNode()->getNodeTransform()->translate(glm::vec3(-0.5, 0, 0));
	//model.getRootNode()->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getNodeTransform()->scale(glm::vec3(10, 2, 2));

	models.push_back(&cubes);
	//models.push_back(&twoB);
	models.push_back(&plane);

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



		////copper
		//glm::vec3 matAmbient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
		//glm::vec3 matDiffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
		//glm::vec3 matSpecular = glm::vec3(0.256777f, 0.137622f, 0.086014f);/*
		glm::vec3 matAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 matDiffuse = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 matSpecular = glm::vec3(0.2f, 0.2f, 0.2f);
		float shininess = 12.8f;

		////unique_ptr<Material> cube = make_unique<Material>(matAmbient, matDiffuse, matSpecular, shininess);

		shader->setVec3("mambient", matAmbient);
		shader->setVec3("mdiffuse", matDiffuse);
		shader->setVec3("mspecular", matSpecular);
		shader->setFloat("mshininess", shininess);


		//glm::vec3 ligDiffuse = lightColor * glm::vec3(0.6f);
		//glm::vec3 ligAmbient = ligDiffuse * glm::vec3(0.9f);
		//glm::vec3 ligSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
		////shader->setVec3("lambient", ligAmbient);
		////shader->setVec3("ldiffuse", ligDiffuse);
		////shader->setVec3("lspecular", ligSpecular);
		//shader->setVec3("lambient", 0.2f, 0.2f, 0.2f);
		//shader->setVec3("ldiffuse", 0.5f, 0.5f, 0.5f);
		//shader->setVec3("lspecular", 1.0f, 1.0f, 1.0f);

		//every light
		glm::vec3 lightColor = glm::vec3(2.0f, 2.0f, 2.0f);
		shader->setVec3("lightColor", lightColor);
		shader->setFloat("currentTime", currentTime);
		shader->setVec3("viewPosition", camera->cameraPos);


		//directional light
		glm::vec3 lightDirection = glm::normalize(glm::vec3(-0.2f, -3.0f, -1.3f));
		shader->setVec3("lightDirection", lightDirection);
		glm::vec3 directionalColors = glm::vec3(0.0f, sin(currentTime) + 1.0f, cos(currentTime) + 1.0f);
		shader->setVec3("directionalColors", directionalColors);

		//point light
		//glm::vec3 pointLightPosition = glm::vec3(1, 1, 1.0f);
		glm::vec3 pointLightPosition = glm::vec3(10 * sin(currentTime), 2.0f, 1.0f);
		shader->setVec3("pointLightPosition", pointLightPosition);

		//spotlight
		shader->setVec3("spotLightPosition", camera->cameraPos);
		shader->setVec3("spotLightDirection", camera->cameraFront);
		shader->setFloat("lightCutOff", glm::cos(glm::radians(3.0f)));
		shader->setFloat("outerLightCutOff", glm::cos(glm::radians(4.5f)));





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
