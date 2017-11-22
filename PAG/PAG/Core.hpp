#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class Window;
class Mesh;
class Shader;
class TextureLoader;
class Camera;
class Scene;

class Core
{
private:
	GLfloat deltaTime = 0.0f;		// Czas pomiêdzy obecn¹ i poprzedni¹ klatk¹
	GLfloat lastTime = 0.0f;		// Czas ostatniej ramki
	float cameraSpeed = 20.0f; 
	float mouseSensivity = 1.0f;

	void processInput();
	void processMouse(Scene scene);

	std::unique_ptr<Window> window;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<TextureLoader> texture;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;
public:
	void run();
	Core();
	~Core();
};

#endif /* Core_hpp */
