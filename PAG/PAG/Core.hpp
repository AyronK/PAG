#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#include <memory>

class Window;
class Mesh;
class Shader;
class Camera;
class Scene;
class MousePicker;

class Core
{
private:
	GLfloat deltaTime = 0.0f;		// Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹
	GLfloat lastTime = 0.0f;		// Czas ostatniej ramki
	float cameraSpeed = 20.0f; 
	float mouseSensivity = 0.05f;

	void processInput();
	void processMouse(Scene scene);

	std::unique_ptr<Window> window;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<MousePicker> mousePicker;
public:
	void run();
	Core();
	~Core();
};

#endif /* Core_hpp */
