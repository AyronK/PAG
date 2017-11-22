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
#include <iostream>
using namespace std;

void Core::run()
{
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//Model robocopModel("/Users/sern19/Desktop/Tmp/2B/2B.fbx");
	Model robocopModel("F:/Studia/Sem V/PAG/PAG/Objects/Tower/Tower.obj");
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

		Transform robocop = Transform();
		robocop.translate(glm::vec3(0.0f, -1.75f, 0.0f));
		robocop.scale(glm::vec3(0.2f, 0.2f, 0.2f));
		shader->setMat4("model", robocop.getTransform());
		robocopModel.Draw(*shader);

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

	texture = std::make_unique<TextureLoader>();

	shader = std::make_unique<Shader>();

	shader->use();

	camera = std::make_unique<Camera>();
	glfwGetCursorPos(window->getWindow(), &camera->lastX, &camera->lastY);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	scene = std::make_unique<Scene>();
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


	float x = (2.0f * mousePosX) / SCREEN_WIDTH - 1.0f;
	float y = 1.0f - (2.0f * mousePosY) / SCREEN_HEIGHT;
	float z = 1.0f;
	glm::vec3 ray_position = glm::vec3(x, y, z);
	
	glm::vec4 ray_front = glm::vec4(ray_position.x, ray_position.y, -1.0, 1.0);
	
	glm::vec4 ray_eye = glm::inverse(scene.getProjectionSpace()) * ray_front;
	ray_eye = glm::vec4(ray_position.x, ray_position.y, -1.0, 0.0);

	glm::vec3 ray_wor = glm::inverse(scene.getViewSpace()) * ray_eye;
		// don't forget to normalise the vector at some point
		ray_wor = glm::normalize(ray_wor);
	cout << ray_wor.x << " " << ray_wor.y << " " << ray_wor.z << endl;


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
