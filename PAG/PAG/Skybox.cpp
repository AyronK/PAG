#include "Skybox.hpp"
#include "Shader.hpp"
#include "Scene.hpp"

using namespace std;


void Skybox::setupSkybox()
{
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	
}

void Skybox::drawContent(Shader * const pShader, Scene * const scene)
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	pShader->use();

	pShader->setMat4("view", scene->getViewSpace());
	pShader->setMat4("projection", scene->getProjectionSpace());

	glBindVertexArray(VertexArrayObject);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(NULL);
	glDepthFunc(GL_LESS); // set depth function back to default
}

Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}
