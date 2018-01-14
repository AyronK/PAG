#include "Skybox.hpp"
#include "TextureLoader.hpp"	

using namespace std;


void Skybox::setupSkybox(vector<string> faces)
{
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	

	skyboxTexture = TextureLoader::loadCubemap(faces);
}

Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}
