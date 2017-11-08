#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "config.hpp"
#include "Transform.hpp"
class Mesh
{
	struct Vertex
	{
		glm::vec3 points;
		glm::vec3 color;
		glm::vec2 texture;
		Vertex(glm::vec3 points) : points(points) {}
		Vertex(glm::vec3 points, glm::vec3 color) : points(points), color(color) {}
		Vertex(glm::vec3 points, glm::vec2 texture) : points(points), texture(texture) {}
		Vertex(glm::vec3 points, glm::vec3 color, glm::vec2 texture) : points(points), color(color), texture(texture) {}
	};

	Vertex vertices[36] = {
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),

		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 0.0f))
	};

public:
	Transform transform;
	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;
	void loadContent();
	void draw();
	Mesh();
	~Mesh();
};

