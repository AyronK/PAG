#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
class Mesh
{
	struct Vertex
	{
		glm::vec3 points;
		glm::vec3 color;
		Vertex(glm::vec3 points, glm::vec3 color) : points(points), color(color){}
	};
	
	//unsigned int indices[3] = { 0, 1, 3 };
	Vertex vertices[3] = {
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
	};

	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;

public:
	void draw();
	Mesh();
	~Mesh();
};

