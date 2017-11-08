#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx/transform.hpp>
#include "config.hpp"
class Mesh
{
	struct Vertex
	{
		glm::vec3 points;
		glm::vec3 color;
		glm::vec2 texture;
		Vertex(glm::vec3 points) : points(points) {}
		Vertex(glm::vec3 points, glm::vec3 color) : points(points), color(color){}
		Vertex(glm::vec3 points, glm::vec3 color, glm::vec2 texture) : points(points), color(color), texture(texture) {}
	};
	
	unsigned int indices[6] = { 0, 1, 2, 
								1, 2, 3 };
	Vertex vertices[18] = {
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f)), //basis
		Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f)), //left side
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(1.0f, 0.0f,  0.0f)),

		Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f)), //right side
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(1.0f, 0.0f,  0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f)), //front side
		Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(1.0f, 0.0f,  0.0f)),

		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f)), //back side
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f,  0.0f)),
		Vertex(glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(1.0f, 0.0f,  0.0f))
	};
	/*Vertex vertices[3] = {
		Vertex(Vertex(glm::vec3(0.5f, 0.75f, 0.0f), Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
		Vertex(Vertex(glm::vec3(-0.5f, 0.75f, 0.0f), Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
		Vertex(Vertex(glm::vec3(0.0f, -0.5f, 0.0f), Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.0f))	
	};*/


public:
	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;
	void loadContent();
	void draw();
	Mesh();
	~Mesh();
};

