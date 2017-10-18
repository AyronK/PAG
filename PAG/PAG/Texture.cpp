#include "Texture.hpp"

Texture::Texture()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// ustaw opcje zawijania/filtrowania tekstury (na aktywnym obiekcie tekstury)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	// za³aduj obraz i wygeneruj obiekt tekstury
	int width, height, nrChannels;
	unsigned char *data = stbi_load("../Textures/bricks.jpg", &width, &height, &nrChannels, 0);

	if (!data)
	{
		throw std::runtime_error("Failed to load texture");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}


Texture::~Texture()
{
}
