#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Textures;
class Node;
class Shader;

class Model
{
private:
	Node* mRootNode = NULL;
	Textures* mTextures = NULL;
	std::string mModelDirectory;
	std::string mModelFilename;
	void getChildrenNodes(Node * node, std::vector<Node*>* allNodes);

	void loadModel(const std::string& pModelPath, Shader *const pShader);
public:
	Model(const std::string& pModelPath, Shader *const pShader);
	Model(const Model& pSourceModel);
	~Model();
	const std::pair<glm::vec4, glm::vec4> calculateModelOBB();
	const std::pair<Node*, float> testRayOBBIntersection(const glm::vec3 & pRaySource, const glm::vec3 & pRayDirection);
	void draw(Shader *const pShader);
	Node* const getRootNode();
	std::vector<Node*> getAllNodes();
};

#endif /* Model_hpp */
