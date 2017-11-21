#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "config.hpp"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Shader;

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};

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
	std::vector<Texture> textures;
	
public:
	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;
	void setupMesh();
	void draw(Shader shader);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();
};

