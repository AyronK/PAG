#ifndef UserInterface_hpp
#define UserInterface_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

class Node;
class Transform;

class UserInterface
{
private:
	bool mShouldShowInterface = false;
	Node* mSelectedNode = NULL;
	Transform* mSelectedTransform = NULL;

	//Stringi do wyœwietlania
	float mTranslateX, mTranslateY, mTranslateZ, mScaleX, mScaleY, mScaleZ, mRotationAngle, mRotationAxisX, mRotationAxisY, mRotationAxisZ;

	void updateUITransformData();
	void updateTransform();
public:
	UserInterface(GLFWwindow* const pWindow);
	void draw();
	void setShouldShowInterface(const bool& pShouldShowInterface);
	void setSelectedNode(Node* const pSelectedNode);
};

#endif /* UserInterface_hpp */