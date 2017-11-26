#pragma once
#include "Material.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Shader;
class Texture;
class Textures
{
private:
	std::vector<Texture> mDiffuseTextures;
	std::vector<Texture> mSpecularTextures;
	std::vector<Texture> mNormalTextures;
	std::string mTexturesPath; 

	void loadTextures(const aiScene* const pScene);
	const bool chcekIfIsLoaded(const std::string& pTexturePath, const std::string& pTextureType);
public:
	Textures(const aiScene* const pScene, const std::string& pTexturesPath, Shader *const pShader);
	~Textures();
	void setActiveTextures(const Material& pMaterial, Shader *const pShader);
	const Material findTexturesForMaterial(aiMaterial* const pMaterial);
};

