#ifndef Material_hpp
#define Material_hpp

#include <vector>
#include <glm/glm.hpp>


struct Material
{
	std::vector<int> mDiffuseTextureID;
	glm::vec3 mDiffuseColor = glm::vec3(0.25f, 0.25f, 0.5f);
	std::vector<int> mSpecularTextureID;
	glm::vec3 mSpecularLevel = glm::vec3(1, 1, 1);
	std::vector<int> mNomralTextureID;
	Material() {};
};

#endif /* Material_hpp */
