#include "Mesh.hpp"
void Mesh::draw()
{
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
}

Mesh::Mesh()
{
	// generate object array
	glGenVertexArrays(1, &VertexArrayObject);
	// bind the Vertex Array Object 
	glBindVertexArray(VertexArrayObject);

	// generate object buffer with size 1
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// generate element buffer with size 1
	glGenBuffers(1, &ElementObjectBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementObjectBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//configure vertex attributes(s).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(sizeof(glm::vec3)*2));
	glEnableVertexAttribArray(2);
}

Mesh::~Mesh()
{
}
