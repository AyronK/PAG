#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Textures.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "MousePicker.hpp"

using namespace std;

void Mesh::drawContent(Shader * const pShader, Textures* const pTextures)
{
	Material temporaryMaterial;
	if (!isSelected) {
		temporaryMaterial = mMaterial;
	}
;
	pTextures->setActiveTextures(temporaryMaterial, pShader);
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


void Mesh::setIsSelected(bool isSelected)
{
	this->isSelected = isSelected;
}

void Mesh::setupMesh() {

	//Generowanie tablicy obiektów
	glGenVertexArrays(1, &VertexArrayObject);
	//Generowanie nowego bufora o rozmiarze 1
	glGenBuffers(1, &VertexBufferObject);
	//Generowanie bufora elementów
	glGenBuffers(1, &ElementObjectBuffer);

	//Bindowanie tablicy obiektów
	glBindVertexArray(VertexArrayObject);

	//Bindowanie bufora, informacja, ¿e zawiera on tablicê wierzcho³ków
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	//Wype³nienie bufora danymi o wierzcho³kach (STATIC_DRAW - wyznaczone raz i odczytywane wielokrotnie)
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementObjectBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Informacja o interpretacji danych - indeks, rozmiar, typ, czy powinien nrmalizowaæ, odleg³oœæ miêdzy wierzcho³kami (w tablicy), odleg³oœæ od pocz¹tku danych (w tablicy)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); //Atrybut wierzcho³ków
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, normals))); //Atrybut koloru - start po wierzcho³kach (glm::vec3)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, texture))); //Atrubut textury

																											//Podanie dostêpu do wierzcho³ków w tablicy o indeksie 0-2
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

Mesh::~Mesh()
{
}

const bool Mesh::checkRayIntersections(const glm::vec3& pRaySource, const glm::vec3& pRayDirection, const glm::mat4& pTransform, float& pDistanceOutput)
{
	int i;
	glm::vec3 triangle[3];
	float distance;
	std::vector<float> distances;
	//Sprawdzanie dla ka¿dego trójk¹ta odleg³oœci
	for (i = 0; i<indices.size(); i += 3)
	{
		//Transformacja
		triangle[0] = glm::vec3(pTransform*glm::vec4(vertices[indices[i]].position, 1.0f)); //PAMIÊTAÆ NA PRZYSZ£OŒÆ O KOLEJNOŒCI - NIE STRACISZ BEZ SENSU GODZINY
		triangle[1] = glm::vec3(pTransform*glm::vec4(vertices[indices[i + 1]].position, 1.0f));
		triangle[2] = glm::vec3(pTransform*glm::vec4(vertices[indices[i + 2]].position, 1.0f));
		if (MousePicker::checkRayIntersectionTriangle(pRaySource, pRayDirection, triangle, distance)) distances.push_back(distance);
	}
	if (distances.size() == 0) return false;
	pDistanceOutput = *std::min_element(std::begin(distances), std::end(distances));
	return true;
}