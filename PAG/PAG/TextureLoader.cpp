#include "TextureLoader.hpp"

void TextureLoader::setActiveTexture(int id)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[id]);
}

unsigned int TextureLoader::getTexture(int id) {
	return textures[id];
}

TextureLoader::TextureLoader()
{
	glGenTextures(24, textures);

	loadTexture("../Textures/particle.bmp", 0);
	loadTexture("../Textures/water.bmp", 1);
	loadTexture("../Textures/ja.jpg", 2);
}

void TextureLoader::loadTexture(std::string name, int id) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	glBindTexture(GL_TEXTURE_2D, textures[id]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char *data = stbi_load(name.data(), &width, &height, &nrChannels, 0);

	if (!data)
	{
		throw std::runtime_error("Failed to load texture");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}


TextureLoader::~TextureLoader()
{
}