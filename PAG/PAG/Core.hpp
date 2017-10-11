#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#include <stdio.h>
#include <glad/glad.h> //Do pobierania funkcji
#include <GLFW/glfw3.h> //G³ówna pêtla i inicjalizacja

class Window;
class Mesh;
class Shader;
class Texture;

class Core
{
private:
	Window* window;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
public:
	void run();
	Core();
	~Core();
};

#endif /* Core_hpp */
