#ifndef Texture_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <stdexcept>
#include <vector>

class TextureLoader
{
public:
	static unsigned int TextureFromFile(const char * path, const std::string & directory, bool gamma = false);
	~TextureLoader();
};


#endif /* Texture_hpp */