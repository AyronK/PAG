#ifndef Texture2_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <stdexcept>

class TextureLoader
{
private:
	unsigned int textures[24];
public:
	void setActiveTexture(int id);
	unsigned int getTexture(int id);
	TextureLoader();
	void loadTexture(std::string name, int id);
	~TextureLoader();
};


#endif /* Texture_hpp */