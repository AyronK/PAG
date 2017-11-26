#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Textures.hpp"
#include "Material.hpp"
#include "Texture.hpp"

using namespace std;

void Mesh::drawContent(Shader * const pShader, Textures* const pTextures)
{
	Material temporaryMaterial;
	//if (!mIsSelected) 
	temporaryMaterial = mMaterial;
	pTextures->setActiveTextures(temporaryMaterial, pShader);
	//Bindowanie tablicy obiekt�w
	glBindVertexArray(VertexArrayObject);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(NULL);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(vertices), indices(indices)
{
	setupMesh();
}

void Mesh::setMaterial(const Material& pMaterial)
{
	mMaterial = pMaterial;
}


void Mesh::setupMesh() {

	//Generowanie tablicy obiekt�w
	glGenVertexArrays(1, &VertexArrayObject);
	//Generowanie nowego bufora o rozmiarze 1
	glGenBuffers(1, &VertexBufferObject);
	//Generowanie bufora element�w
	glGenBuffers(1, &ElementObjectBuffer);

	//Bindowanie tablicy obiekt�w
	glBindVertexArray(VertexArrayObject);

	//Bindowanie bufora, informacja, �e zawiera on tablic� wierzcho�k�w
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	//Wype�nienie bufora danymi o wierzcho�kach (STATIC_DRAW - wyznaczone raz i odczytywane wielokrotnie)
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementObjectBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Informacja o interpretacji danych - indeks, rozmiar, typ, czy powinien nrmalizowa�, odleg�o�� mi�dzy wierzcho�kami (w tablicy), odleg�o�� od pocz�tku danych (w tablicy)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); //Atrybut wierzcho�k�w
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, normals))); //Atrybut koloru - start po wierzcho�kach (glm::vec3)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, texture))); //Atrubut textury

																											//Podanie dost�pu do wierzcho�k�w w tablicy o indeksie 0-2
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

Mesh::~Mesh()
{
}