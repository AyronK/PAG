#ifndef Texture_hpp
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <stdexcept>

class Texture
{
private:
	unsigned int texture[2];
public:
	void loadTexture();
	unsigned int getTexture(int id);
	Texture();
	~Texture();
};


#endif /* Texture_hpp */