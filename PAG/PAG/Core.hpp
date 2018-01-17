#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#include <memory>
#include <vector>

class Window;
class Mesh;
class Shader;
class Camera;
class Scene;
class MousePicker;
class Model;
class UserInterface;
class CParticleSystemTransformFeedback;

class Core
{
private:
	bool cameraMove = true;
	GLfloat deltaTime = 0.0f;		// Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹
	GLfloat lastTime = 0.0f;		// Czas ostatniej ramki
	float cameraSpeed = 2.0f;
	float mouseSensivity = 0.125f;

	void processInput();
	void processMouse(Scene scene, std::vector<Model*> models);

	//HDR
	bool hdr = true;
	bool hdrKeyPressed = false;
	float exposure = 1.0f;

	std::unique_ptr<Window> window;
	std::unique_ptr<Shader> defaultShader;
	std::unique_ptr<Shader> particlesShader;
	std::unique_ptr<Shader> particlesRenderingShader;
	std::unique_ptr<Shader> skyboxShader;
	std::unique_ptr<Shader> screenShader;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<CParticleSystemTransformFeedback> particleSystem;
	std::unique_ptr<MousePicker> mousePicker;
	std::unique_ptr<UserInterface> ui;
public:
	void run();
	Core();
	~Core();
};

#endif /* Core_hpp */
