#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
private:
	std::string mTexturePath;
	GLuint mTexture;

	void loadTexture(const std::string& pTexturePath);
public:
	Texture(const std::string& pTexturePath);
	Texture(const Texture& pSourceTexture);
	~Texture();
	static void deselectAllTextures();
	void selectActiveTexture(const std::string& pTextureType, const unsigned int& pTextureNumber);
	const std::string& getTexturePath();
};

#endif /* Texture_hpp */
