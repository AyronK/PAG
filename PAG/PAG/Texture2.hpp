#ifndef Texture2_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <stdexcept>

class Texture2
{
private:
	unsigned int textures[24];
public:
	void setActiveTexture(int id);
	unsigned int getTexture(int id);
	Texture2();
	void loadTexture(std::string name, int id);
	~Texture2();
};


#endif /* Texture_hpp */