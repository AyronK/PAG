#pragma once
#include <glad/glad.h>
class Mesh
{
private:
	unsigned int indices[3] = { 0, 1, 3 };
	float vertices[9] = {
		0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};

	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;

public:
	void draw();
	void load();
	Mesh();
	~Mesh();
};

