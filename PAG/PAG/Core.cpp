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
bool particlesEnabled = true;

bool useNightvision = false;
DWORD next_game_tick = clock();
int loops;

void Core::run()
{
	TextureLoader texture;
	int sleep_time = 0;

	bool game_is_running = true;
	float timeval = 0, lasttimeVel = 0;


	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	std::vector<Model*> models;
	//Model cubes("F:/Studia/Sem V/PAG/PAG/Objects/Cubes/source/Cubes.fbx", defaultShader.get());
	//Model nano("F:/Studia/Sem V/PAG/PAG/Objects/nanosuit/source/nanosuit.obj", defaultShader.get());
	//Model nano2("F:/Studia/Sem V/PAG/PAG/Objects/nanosuit/source/nanosuit.obj", defaultShader.get());
	//Model lambo("F:/Studia/Sem V/PAG/PAG/Objects/Lambo/source/Avent.obj", defaultShader.get());
	//Model plane("F:/Studia/Sem V/PAG/PAG/Objects/Plane/source/plane.FBX", defaultShader.get());


	Model cubes("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/Cubes/source/Cubes.fbx", defaultShader.get());
	Model nano("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/nanosuit/source/nanosuit.obj", defaultShader.get());
	Model plane("C:/Users/Ayron/Desktop/Studia/PAG/PAG/Objects/Plane/source/plane.FBX", defaultShader.get());


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe

	cubes.getRootNode()->getNodeTransform()->scale(glm::vec3(0.005, 0.005, 0.005));
	nano.getRootNode()->getNodeTransform()->translate(glm::vec3(3.0f, 5.0f, 0.0f));
	nano.getRootNode()->getNodeTransform()->scale(glm::vec3(0.07, 0.07, 0.07));
	//lambo.getRootNode()->getNodeTransform()->scale(glm::vec3(0.25, 0.25, 0.25));
	//lambo.getRootNode()->getNodeTransform()->translate(glm::vec3(-5.0f, 0.0f, 0.0f));
	//model.getRootNode()->getNodeTransform()->translate(glm::vec3(-0.5, 0, 0));
	//model.getRootNode()->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getChild(0)->getNodeTransform()->scale(glm::vec3(10, 2, 2));

	models.push_back(&cubes);
	models.push_back(&nano);
	//models.push_back(&lambo);
	models.push_back(&plane);

	//sparkling - 2
	particleSystem->SetGeneratorProperties(
		glm::vec3(0.5f, 0.60f, 0.0f), // position
		glm::vec3(-0.1, -0.1, -0.1), // Minimal velocity
		glm::vec3(0.1, 0.1, 0.1f), // Maximal velocity
		glm::vec3(0, 0, 0), // Gravity force 
		glm::vec3(1.0f, 0.9f, 0.1f), // Color 
		3.0f, // Minimum lifetime in seconds
		5.0f, // Maximum lifetime in seconds
		0.03f, // Rendered size
		0.5f, // Spawn every 
		10); // count of particles

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
	defaultShader->setInt("skybox", skyboxTexture);

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	// screen quad VAO
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// framebuffer configuration
	// -------------------------
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	 glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
  																							  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	screenShader->setInt("screenTexture", textureColorbuffer);
	screenShader->setInt("hdrBuffer", 0);

	while (!glfwWindowShouldClose(window->getWindow()) && game_is_running)
	{
		loops = 0;
		while (clock() > next_game_tick && loops < MAX_FRAMESKIP) {
			next_game_tick += SKIP_TICKS;
			loops++;
		}
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		processInput();
		processMouse(*scene, models);

		// render
		// ------
		// bind to framebuffer and draw scene as we normally would to color texture 
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

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
		defaultShader->setFloat("animatedIntensity", 1.1);// -cos(currentTime / 2.0));

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

		for (auto model : models)
		{
			if (model == &nano) {
				defaultShader->setBool("shouldReflect", true);
				defaultShader->setBool("shouldRefract", false);
			}
			else {
				defaultShader->setBool("shouldReflect", false);
				defaultShader->setBool("shouldRefract", false);
			}
			model->draw(defaultShader.get());
		}

		defaultShader->setBool("shouldReflect", false);
		defaultShader->setBool("shouldRefract", true);

		nano.getRootNode()->getNodeTransform()->translate(glm::vec3(15.0f, 0.0f, 0.0f));
		nano.draw(defaultShader.get());


		defaultShader->setBool("shouldReflect", false);
		defaultShader->setBool("shouldRefract", false);

		/*nano.getRootNode()->getNodeTransform()->translate(glm::vec3(15.0f, 0.0f, 0.0f));
		nano.draw(defaultShader.get());
		nano.getRootNode()->getNodeTransform()->translate(glm::vec3(-30.0f, 0.0f, 0.0f));*/

		texture.setActiveTexture(0);

		//particleSystem->SetMatrices(&scene->getProjectionSpace(), camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp); //Nie ladnie, nie bierze sie adresu tymczasowego obiektu :c
		glm::mat4 dirtyFix = scene->getProjectionSpace();
		particleSystem->SetMatrices(&dirtyFix, camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);
		//

		timeval = clock();
		float interval = float(timeval - lasttimeVel) / float(1000);
		lasttimeVel = timeval;

		skybox.drawContent(skyboxShader.get(), scene.get());

		if (particlesEnabled) {
			particleSystem->UpdateParticles(interval, particlesShader.get());
			particleSystem->RenderParticles(particlesRenderingShader.get());
		}

		ui->draw();



		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader->use();
		glBindVertexArray(quadVAO);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
								  // clear all relevant buffers
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer); // use the color attachment texture as the texture of the quad plane
		texture.setActiveTexture(2);
		screenShader->setInt("noiseTex", texture.getTexture(1));
		screenShader->setFloat("elapsedTime", currentTime);
		screenShader->setBool("useNightVision", useNightvision);
		screenShader->setInt("hdr", hdr);
		screenShader->setFloat("exposure", exposure);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}

	glDeleteFramebuffers(1, &framebuffer);
}

Core::Core()
{
	// glfw: initialize and configure
	if (!glfwInit())
		throw runtime_error("Cannot initialize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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


	screenShader = std::make_unique<Shader>();

	screenShader->loadShader(GL_VERTEX_SHADER, "../Shaders/framebuffers_screen.vert");
	screenShader->loadShader(GL_FRAGMENT_SHADER, "../Shaders/framebuffers_screen.frag");
	screenShader->link();

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

	if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && !hdrKeyPressed)
	{
		hdr = !hdr;
		hdrKeyPressed = true;
	}
	if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		hdrKeyPressed = false;
	}

	if (glfwGetKey(window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (exposure > 0.0f)
			exposure -= 0.05f;
		else
			exposure = 0.0f;
	}
	else if (glfwGetKey(window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		exposure += 0.05f;
	}

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

	if (glfwGetKey(window->getWindow(), GLFW_KEY_P) == GLFW_PRESS)
	{
		particlesEnabled = !particlesEnabled;
	}

	if (glfwGetKey(window->getWindow(), GLFW_KEY_N) == GLFW_PRESS)
	{
		useNightvision = !useNightvision;
	}

	if (glfwGetKey(window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		cameraMove = !cameraMove;
	}

	if (glfwGetKey(window->getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
		//fire
		{
			particleSystem->SetGeneratorProperties(
				glm::vec3(0.0f, 0.25f, 0.0f), // position
				glm::vec3(-0.025, 0.3, -0.025), // Minimal velocity
				glm::vec3(0.025, 0.05, 0.025f), // Maximal velocity
				glm::vec3(0, 0, 0), // Gravity force 
				glm::vec3(1.0f, 0.3f, 0.1f), // Color 
				13.5f, // Minimum lifetime in seconds
				45.0f, // Maximum lifetime in seconds
				0.04f, // Rendered size
				0.01f, // Spawn every 
				1); // count of particles
		}
	}
	else if (glfwGetKey(window->getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
		//sparkling
		{
			particleSystem->SetGeneratorProperties(
				glm::vec3(0.5f, 0.60f, 0.0f), // position
				glm::vec3(-0.1, -0.1, -0.1), // Minimal velocity
				glm::vec3(0.1, 0.1, 0.1f), // Maximal velocity
				glm::vec3(0, 0, 0), // Gravity force 
				glm::vec3(1.0f, 0.9f, 0.1f), // Color 
				3.0f, // Minimum lifetime in seconds
				5.0f, // Maximum lifetime in seconds
				0.03f, // Rendered size
				0.5f, // Spawn every 
				10); // count of particles
		}
	}
	else if (glfwGetKey(window->getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
		//water
		{
			particleSystem->SetGeneratorProperties(
				glm::vec3(1.0f, 1.0f, 0.0f), // position
				glm::vec3(-0.05, -0.2, -0.05), // Minimal velocity
				glm::vec3(0.05, 0.0, 0.05f), // Maximal velocity
				glm::vec3(0, -2.5, 0), // Gravity force 
				glm::vec3(0.25f, 0.45f, 0.7f), // Color 
				13.5f, // Minimum lifetime in seconds
				45.0f, // Maximum lifetime in seconds
				0.04f, // Rendered size
				0.0001f, // Spawn every 
				2); // count of particles
		}
	}

	if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		for (auto model : models)
		{
			for (auto node : model->getAllNodes()) {
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
