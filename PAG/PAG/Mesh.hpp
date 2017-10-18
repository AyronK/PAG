#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
class Mesh
{
	struct Vertex
	{
		glm::vec3 points;
		glm::vec3 color;
		glm::vec2 texture;
		Vertex(glm::vec3 points, glm::vec3 color) : points(points), color(color){}
		Vertex(glm::vec3 points, glm::vec3 color, glm::vec2 texture) : points(points), color(color), texture(texture) {}
	};
	
	unsigned int indices[3] = { 0, 1, 2 };
	Vertex vertices[3] = {
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 1.0f)),	// up
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),	// right
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f))	// left
	};

	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;

public:
	void draw();
	Mesh();
	~Mesh();
};

