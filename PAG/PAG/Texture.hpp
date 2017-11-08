#ifndef Texture_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <stdexcept>

class Texture
{
private:
	unsigned int textures[24];
public:
	void setActiveTexture(int id);
	unsigned int getTexture(int id);
	Texture();
	void loadTexture(std::string name, int id);
	~Texture();
};


#endif /* Texture_hpp */