#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "config.hpp"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Material.hpp"

class Shader;
class Textures;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 texture;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

class Mesh
{
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	Material mMaterial;
	bool isSelected;
	
public:
	void setIsSelected(bool isSelected);
	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;
	void setupMesh();
	void drawContent(Shader* const pShader, Textures* const pTextures);
	Mesh(std::vector<Vertex>, std::vector<unsigned int> indices);
	void setMaterial(const Material& pMaterial);
	~Mesh();
	const bool checkRayIntersections(const glm::vec3 & pRaySource, const glm::vec3 & pRayDirection, const glm::mat4 & pTransform, float & pDistanceOutput);
};

