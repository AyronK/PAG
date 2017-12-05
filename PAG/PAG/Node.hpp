#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/scene.h>

class Transform;
class Mesh;
class Shader;
class Textures;

class Node
{
private:
    Transform* mElementTransform=NULL; //Dla uproszczenia przyjmijmy, że może mieć tylko 1 gałąź dzieci, jest zawsze w parze z mCachedTransform
    Node* mParentNode=NULL;
    const aiMatrix4x4 mOriginalTransform;
    std::vector<Node> mChildNodes;
    std::vector<Mesh> mMeshes;
    
    Node(const aiNode* const pNode, const aiScene* const pScene, Node* const pParentNode, Textures* const pTextures);
    void processNode(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures);
    Mesh processMesh(const aiMesh* const pMesh, const aiScene* const pScene, Textures* const pTextures);
    void updateChildrenPointers(Node* const pParent); 
public:
    Node(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures);
    Node(const Node& pSourceNode);
    ~Node();
	std::pair<bool, float> tryGetIntersection(const glm::vec3 & pRaySource, const glm::vec3 & pRayDirection);
    
    void setIsSelected(const bool& pIsSelected);

	void drawContent(Shader *const pShader, Textures* const pTextures);
    void resetNodeTransform();
    
    const unsigned int getChildrensCount();
    const unsigned int getNodeLevel();
    Transform* const getNodeTransform();
	Transform getHierarchyTransform();
	Node* const getParentNode();
    Node* const getChild(const unsigned int& pChildNumber);
};

#endif /* Node_hpp */
