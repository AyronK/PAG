#ifndef Texture_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <stdexcept>
#include <vector>

class TextureLoader
{
private:
	static unsigned int textures[24];
public:
	/*void setActiveTexture(int id);
	unsigned int getTexture(int id);
	TextureLoader();*/

	static unsigned int TextureFromFile(const char * path, const std::string & directory, bool gamma = false);
	static void loadTexture(std::string name, int id);

	~TextureLoader();
};


#endif /* Texture_hpp */