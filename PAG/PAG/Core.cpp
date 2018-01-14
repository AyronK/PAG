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
#include "CParticleSystemTransformFeedback.hpp"
#include "UserInterface.hpp"
#include "TextureLoader.hpp"
#include <ctime>
#include "Skybox.hpp"
using namespace std;

const int FRAMES_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int MAX_FRAMESKIP = 10;

DWORD next_game_tick = GetTickCount();
int loops;

void Core::run()
{
	int sleep_time = 0;

	bool game_is_running = true;
	float timeval = 0, lasttimeVel = 0;


	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	std::vector<Model*> models;
	Model cubes("F:/Studia/Sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", defaultShader.get());
	//Model nano("F:/Studia/Sem V/PAG/PAG/Objects/nanosuit/source/nanosuit.obj", shader.get());
	//Model lambo("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/Lambo/source/Avent.obj", shader.get());
	Model plane("F:/Studia/Sem V/PAG/PAG/Objects/Plane/source/plane.FBX", defaultShader.get());

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe

	cubes.getRootNode()->getNodeTransform()->scale(glm::vec3(0.005, 0.005, 0.005));
	//nano.getRootNode()->getNodeTransform()->translate(glm::vec3(3.0f, 0.0f, 0.0f));
	//nano.getRootNode()->getNodeTransform()->scale(glm::vec3(0.07, 0.07, 0.07));
	//lambo.getRootNode()->getNodeTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
	//lambo.getRootNode()->getNodeTransform()->translate(glm::vec3(-5.0f, 0.0f, 0.0f));
	//model.getRootNode()->getNodeTransform()->translate(glm::vec3(-0.5, 0, 0));
	//model.getRootNode()->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getNodeTransform()->scale(glm::vec3(10, 2, 2));

	models.push_back(&cubes);
	//models.push_back(&nano);
	models.push_back(&plane);
	TextureLoader texture;
	//fire
	//{
	//	particleSystem->SetGeneratorProperties(
	//		glm::vec3(0.0f, 0.25f, 0.0f), // position
	//		glm::vec3(-0.025, 0.3, -0.025), // Minimal velocity
	//		glm::vec3(0.025, 0.05, 0.025f), // Maximal velocity
	//		glm::vec3(0, 0, 0), // Gravity force 
	//		glm::vec3(1.0f, 0.5f, 0.0f), // Color 
	//		13.5f, // Minimum lifetime in seconds
	//		45.0f, // Maximum lifetime in seconds
	//		0.04f, // Rendered size
	//		0.01f, // Spawn every 
	//		1); // count of particles
	//}
	//water
	{
		particleSystem->SetGeneratorProperties(
			glm::vec3(1.0f, 1.0f, 0.0f), // position
			glm::vec3(-0.05, -0.2, -0.05), // Minimal velocity
			glm::vec3(0.05, 0.0, 0.05f), // Maximal velocity
			glm::vec3(0, -2.5, 0), // Gravity force 
			glm::vec3(0.25f, 0.45f, 0.8f), // Color 
			13.5f, // Minimum lifetime in seconds
			45.0f, // Maximum lifetime in seconds
			0.03f, // Rendered size
			0.0001f, // Spawn every 
			2); // count of particles
	}
	//sparkling
	//{
	//	particleSystem->SetGeneratorProperties(
	//		glm::vec3(0.5f, 0.60f, 0.0f), // position
	//		glm::vec3(-0.1, -0.1, -0.1), // Minimal velocity
	//		glm::vec3(0.1, 0.1, 0.1f), // Maximal velocity
	//		glm::vec3(0, 0, 0), // Gravity force 
	//		glm::vec3(1.0f, 0.9f, 0.1f), // Color 
	//		3.0f, // Minimum lifetime in seconds
	//		5.0f, // Maximum lifetime in seconds
	//		0.03f, // Rendered size
	//		0.5f, // Spawn every 
	//		10); // count of particles
	//}

	Skybox skybox;
	skybox.setupSkybox();

	unsigned int skyboxTexture = TextureLoader::loadCubemap(std::vector<std::string>
	{
		"../Textures/Skybox/right.jpg",
			"../Textures/Skybox/left.jpg",
			"../Textures/Skybox/top.jpg",
			"../Textures/Skybox/bottom.jpg",
			"../Textures/Skybox/back.jpg",
			"../Textures/Skybox/front.jpg"
	});

	skyboxShader->setInt("skybox", skyboxTexture);

	while (!glfwWindowShouldClose(window->getWindow()) && game_is_running)
	{
		loops = 0;
		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
			next_game_tick += SKIP_TICKS;
			loops++;
		}
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput();
		processMouse(*scene, models);

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		defaultShader->use();

		glm::vec3 matAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 matDiffuse = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 matSpecular = glm::vec3(0.2f, 0.2f, 0.2f);
		float shininess = 12.8f;

		defaultShader->setVec3("mambient", matAmbient);
		defaultShader->setVec3("mdiffuse", matDiffuse);
		defaultShader->setVec3("mspecular", matSpecular);
		defaultShader->setFloat("mshininess", shininess);

		glm::vec3 lightColor = glm::vec3(2.0f, 2.0f, 2.0f);

		defaultShader->setVec3("lightColor", lightColor);
		defaultShader->setFloat("currentTime", currentTime);
		defaultShader->setFloat("animatedIntensity", 1.1 - cos(currentTime / 2.0));

		defaultShader->setVec3("viewPosition", camera->cameraPos);


		glm::vec3 lightDirection = glm::normalize(glm::vec3(-0.2f, -3.0f, -1.3f));
		defaultShader->setVec3("directionalLightDirection", lightDirection);

		glm::vec3 pointLightPosition = glm::vec3(5 * sin(currentTime), 0.2f, 5 * cos(currentTime));
		defaultShader->setVec3("pointLightPosition", pointLightPosition);

		defaultShader->setVec3("spotLightPosition", camera->cameraPos);
		defaultShader->setVec3("spotLightDirection", camera->cameraFront);
		defaultShader->setFloat("lightCutOff", glm::cos(glm::radians(3.0f)));
		defaultShader->setFloat("outerLightCutOff", glm::cos(glm::radians(7.5f)));

		glm::vec3 spotColors = glm::vec3(-sin(currentTime) + 1.0f, sin(currentTime) + 1.0f, cos(currentTime) + 1.0f);
		defaultShader->setVec3("spotColors", spotColors);

		scene->updateViewSpace(*camera);
		defaultShader->updateScene(*scene);

		for each (auto model in models)
		{
			model->draw(defaultShader.get());
		}
		ui->draw();


		//fire
		//texture.setActiveTexture(0);
		//water
		texture.setActiveTexture(1);

		particleSystem->SetMatrices(&scene->getProjectionSpace(), camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);
		timeval = clock();
		float interval = float(timeval - lasttimeVel) / float(1000);
		lasttimeVel = timeval;

		skybox.drawContent(skyboxShader.get(), scene.get());

		particleSystem->UpdateParticles(interval, particlesShader.get());
		particleSystem->RenderParticles(particlesRenderingShader.get());


		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
}

Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = std::make_unique<Window>();

	// glad: load all OpenGL function pointers
	if (!gladLoadGL())
		throw runtime_error("Cannot initialize GLAD");

	glEnable(GL_DEPTH_TEST);


	defaultShader = std::make_unique<Shader>();


	defaultShader->loadShader(GL_VERTEX_SHADER, DEFAULT_VERTEX_SHADER_PATH);
	defaultShader->loadShader(GL_FRAGMENT_SHADER, DEFAULT_FRAGMENT_SHADER_PATH);
	defaultShader->link();


	particlesShader = std::make_unique<Shader>();

	particlesRenderingShader = std::make_unique<Shader>();

	skyboxShader = std::make_unique<Shader>();

	skyboxShader->loadShader(GL_VERTEX_SHADER, SKYBOX_VERTEX_SHADER_PATH);
	skyboxShader->loadShader(GL_FRAGMENT_SHADER, SKYBOX_FRAGMENT_SHADER_PATH);
	skyboxShader->link();

	camera = std::make_unique<Camera>();
	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	scene = std::make_unique<Scene>();
	ui = std::make_unique<UserInterface>(window->getWindow());
	mousePicker = std::make_unique<MousePicker>();

	particleSystem = std::make_unique<CParticleSystemTransformFeedback>();
	particleSystem->InitalizeParticleSystem(particlesShader.get(), particlesRenderingShader.get());
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
