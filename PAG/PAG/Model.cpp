// Model.cpp
//
// Copyright (c) 2017 Krystian Owoc
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Model.hpp"
#include "Textures.hpp"
#include "Texture.hpp"
#include "Node.hpp"
#include "Config.hpp"

#include "MousePicker.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(const std::string& pModelPath, Shader *const pShader)
{
	loadModel(pModelPath, pShader);
}

Model::Model(const Model& pSourceModel) : mModelDirectory(pSourceModel.mModelDirectory)
{
	mRootNode = new Node(*pSourceModel.mRootNode);
	mTextures = new Textures(*pSourceModel.mTextures);
}

void Model::loadModel(const std::string &pModelPath, Shader *const pShader)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(pModelPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string outputMessage = "(Model::loadModel): B³¹d wczytywania modelu\n\t(ASSIMP): ";
		outputMessage += importer.GetErrorString();
		throw std::runtime_error(outputMessage);
	}

	mModelDirectory = pModelPath;
	mModelDirectory.erase(mModelDirectory.find(MODEL_SOURCE_FOLDER));
	mModelFilename = pModelPath.substr(pModelPath.rfind(MODEL_SOURCE_FOLDER) + std::string(MODEL_SOURCE_FOLDER).length());

	mTextures = new Textures(scene, mModelDirectory.append(MODEL_TEXTURE_FOLDER), pShader);
	mRootNode = new Node(scene->mRootNode, scene, mTextures);
}

void Model::draw(Shader *const pShader)
{
	int i;
	if (mRootNode)
	{		
		mRootNode->drawContent(pShader, mTextures);
	}
}

Node* const Model::getRootNode() { return mRootNode; }

std::vector<Node*> Model::getAllNodes()
{
	std::vector<Node*> allNodes;
	getChildrenNodes(mRootNode, &allNodes);
	return allNodes;
}

void Model::getChildrenNodes(Node* node, std::vector<Node*>* allNodes)
{
	allNodes->push_back(node);
	for (int i = 0; i < node->getChildrensCount(); i++) {
		getChildrenNodes(node->getChild(i), allNodes);
	}
}

Model::~Model()
{
	if (mRootNode) delete mRootNode;
	if (mTextures) delete mTextures;
}