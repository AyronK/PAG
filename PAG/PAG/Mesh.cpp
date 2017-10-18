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
	// generate object buffer with size 1
	glGenBuffers(1, &VertexBufferObject);
	// generate element buffer with size 1
	glGenBuffers(1, &ElementObjectBuffer);

	// bind the Vertex Array Object 
	glBindVertexArray(VertexArrayObject);
	// bind and set vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementObjectBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//configure vertex attributes(s).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}


Mesh::~Mesh()
{
}
