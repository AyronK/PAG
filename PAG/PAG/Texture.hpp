#ifndef Texture_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <stdexcept>

class Texture
{
public:
	void loadTexture();
	Texture();
	~Texture();
};


#endif /* Texture_hpp */