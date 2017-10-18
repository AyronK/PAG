#ifndef Core_hpp
#define Core_hpp
#define GLFW_INCLUDE_NONE

#include <memory>

class Window;
class Mesh;
class Shader;
class Texture;

class Core
{
private:
	std::unique_ptr<Window> window;
	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> texture;
public:
	void run();
	Core();
	~Core();
};

#endif /* Core_hpp */
