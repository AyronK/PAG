#include "Textures.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


Textures::Textures(const aiScene* const pScene, const std::string& pTexturesPath, Shader *const pShader) : mTexturesPath(pTexturesPath)
{
	loadTextures(pScene);
	//Przypisywanie tekstur
	pShader->setInt("diffuse0", 0); //Docelowo przy normalnych i specularach, w jakiejœ pêtli
}

void Textures::loadTextures(const aiScene* const pScene)
{
	int i, j;
	for (i = 0; i<pScene->mNumMaterials; i++)
	{
		if (pScene->mMaterials[i] != NULL)
		{
			//Diffuse
			for (j = 0; j<pScene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE); j++)
			{
				aiString textureName;
				std::string texturePath = mTexturesPath;
				pScene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, j, &textureName);
				texturePath.append(textureName.C_Str());
				if (!chcekIfIsLoaded(texturePath, DIFFUSE_NAME))
				{
					try
					{
						mDiffuseTextures.push_back(Texture(texturePath));
					}
					catch (std::runtime_error err) { throw err; }
				}
			}
			//Specular
			for (j = 0; j<pScene->mMaterials[i]->GetTextureCount(aiTextureType_SPECULAR); j++)
			{
				aiString textureName;
				std::string texturePath = mTexturesPath;
				pScene->mMaterials[i]->GetTexture(aiTextureType_SPECULAR, j, &textureName);
				texturePath.append(textureName.C_Str());
				if (!chcekIfIsLoaded(texturePath, SPECULAR_NAME))
				{
					try
					{
						mSpecularTextures.push_back(Texture(texturePath));
					}
					catch (std::runtime_error err) { throw err; }
				}
			}
			//Normal
			for (j = 0; j<pScene->mMaterials[i]->GetTextureCount(aiTextureType_NORMALS); j++)
			{
				aiString textureName;
				std::string texturePath = mTexturesPath;
				pScene->mMaterials[i]->GetTexture(aiTextureType_NORMALS, j, &textureName);
				texturePath.append(textureName.C_Str());
				if (!chcekIfIsLoaded(texturePath, NORMAL_NAME))
				{
					try
					{
						mNormalTextures.push_back(Texture(texturePath));
					}
					catch (std::runtime_error err) { throw err; }
				}
			}
		}
	}
}

const bool Textures::chcekIfIsLoaded(const std::string& pTexturePath, const std::string& pTextureType)
{
	int i;
	if (pTextureType.compare(DIFFUSE_NAME) == 0)
	{
		for (i = 0; i<mDiffuseTextures.size(); i++)
			if (mDiffuseTextures[i].getTexturePath().compare(pTexturePath) == 0) return true;
	}
	else if (pTextureType.compare(SPECULAR_NAME) == 0)
	{
		for (i = 0; i<mSpecularTextures.size(); i++)
			if (mSpecularTextures[i].getTexturePath().compare(pTexturePath) == 0) return true;
	}
	else if (pTextureType.compare(NORMAL_NAME) == 0)
	{
		for (i = 0; i<mNormalTextures.size(); i++)
			if (mNormalTextures[i].getTexturePath().compare(pTexturePath) == 0) return true;
	}
	return false;
}

Textures::~Textures()
{
}

const Material Textures::findTexturesForMaterial(aiMaterial* const pMaterial)
{
	Material output;
	aiColor3D temporaryColor;
	int i, j;
	//Diffuse
	pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, temporaryColor);
	output.mDiffuseColor = glm::vec4(temporaryColor.r, temporaryColor.g, temporaryColor.b, 1);
	for (i = 0; i<pMaterial->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString textureName;
		std::string texturePath = mTexturesPath;
		pMaterial->GetTexture(aiTextureType_DIFFUSE, i, &textureName);
		texturePath.append(textureName.C_Str());
		for (j = 0; j<mDiffuseTextures.size(); j++)
			if (mDiffuseTextures[j].getTexturePath().compare(texturePath) == 0) output.mDiffuseTextureID.push_back(j);
	}
	//Specular
	pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, temporaryColor);
	output.mSpecularLevel = glm::vec4(temporaryColor.r, temporaryColor.g, temporaryColor.b, 1);
	for (i = 0; i<pMaterial->GetTextureCount(aiTextureType_SPECULAR); i++)
	{
		aiString textureName;
		std::string texturePath = mTexturesPath;
		pMaterial->GetTexture(aiTextureType_SPECULAR, i, &textureName);
		texturePath.append(textureName.C_Str());
		for (j = 0; j<mSpecularTextures.size(); j++)
			if (mSpecularTextures[j].getTexturePath().compare(texturePath) == 0) output.mSpecularTextureID.push_back(j);
	}
	//Normal
	for (i = 0; i<pMaterial->GetTextureCount(aiTextureType_NORMALS); i++)
	{
		aiString textureName;
		std::string texturePath = mTexturesPath;
		pMaterial->GetTexture(aiTextureType_NORMALS, i, &textureName);
		texturePath.append(textureName.C_Str());
		for (j = 0; j<mNormalTextures.size(); j++)
			if (mNormalTextures[j].getTexturePath().compare(texturePath) == 0) output.mNomralTextureID.push_back(j);
	}
	return output;
}

void Textures::setActiveTextures(const Material& pMaterial, Shader *const pShader)
{
	int i;
	//Sprawdzanie czy materia³ u¿ywa tekstur
	pShader->setVec3("diffuseColor", pMaterial.mDiffuseColor);
	if (pMaterial.mDiffuseTextureID.size() == 0) pShader->setBool("shouldUseDiffuseTexture", false);
	else pShader->setBool("shouldUseDiffuseTexture", true);
	//    if (pMaterial.mSpecularTextureID.size()==0)
	//    {
	//        pShader->setBool("shouldUseSpecularTexture", false);
	//    }
	//    else pShader->setBool("shouldUseSpecularTexture", true);
	//    if (pMaterial.mNomralTextureID.size()==0)
	//    {
	//        pShader->setBool("shouldUseNormalTexture", false);
	//    }
	//    else pShader->setBool("shouldUseNormalTexture", true);

	//Przypisywanie tekstur

	Texture::deselectAllTextures();
	for (i = 0; i<pMaterial.mDiffuseTextureID.size(); i++)
		mDiffuseTextures[pMaterial.mDiffuseTextureID[i]].selectActiveTexture(DIFFUSE_NAME, i);
	for (i = 0; i<pMaterial.mSpecularTextureID.size(); i++)
		mSpecularTextures[pMaterial.mSpecularTextureID[i]].selectActiveTexture(SPECULAR_NAME, i);
	for (i = 0; i<pMaterial.mNomralTextureID.size(); i++)
		mNormalTextures[pMaterial.mNomralTextureID[i]].selectActiveTexture(NORMAL_NAME, i);
}
