#include "UserInterface.hpp"
#include "Node.hpp"
#include "Transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include <algorithm>
#include <iterator>


UserInterface::UserInterface(GLFWwindow* const pWindow)
{
	ImGui_ImplGlfwGL3_Init(pWindow, true);
}

void UserInterface::updateUITransformData()
{
	if (mSelectedTransform != NULL)
	{
		mTranslateX = mSelectedTransform->getPosition().x;
		mTranslateY = mSelectedTransform->getPosition().y;
		mTranslateZ = mSelectedTransform->getPosition().z;
		mScaleX = mSelectedTransform->getScale().x;
		mScaleY = mSelectedTransform->getScale().y;
		mScaleZ = mSelectedTransform->getScale().z;
		mRotationAngle = mSelectedTransform->getRotationAxisAndAngle().second;
		mRotationAxisX = mSelectedTransform->getRotationAxisAndAngle().first.x;
		mRotationAxisY = mSelectedTransform->getRotationAxisAndAngle().first.y;
		mRotationAxisZ = mSelectedTransform->getRotationAxisAndAngle().first.z;
	}
}

void UserInterface::updateTransform()
{
	glm::vec3 temporaryValues;
	//Position
	temporaryValues.x = mTranslateX;
	temporaryValues.y = mTranslateY;
	temporaryValues.z = mTranslateZ;
	mSelectedTransform->setPosition(temporaryValues);
	//Scale
	temporaryValues.x = mScaleX;
	temporaryValues.y = mScaleY;
	temporaryValues.z = mScaleZ;
	mSelectedTransform->setScale(temporaryValues);
	//Rotation
	temporaryValues.x = mRotationAxisX;
	temporaryValues.y = mRotationAxisY;
	temporaryValues.z = mRotationAxisZ;
	mSelectedTransform->setRotation(mRotationAngle, temporaryValues);
}

void UserInterface::draw()
{
	static bool* temporaryBool = NULL; //Fix dla pokazuj¹cego siê przyciusku X

	ImGui_ImplGlfwGL3_NewFrame();
	int mainMenuHeight;
	ImGui::BeginMainMenuBar();
	mainMenuHeight = ImGui::GetWindowSize().y;
	ImGui::EndMainMenuBar();
	if (mSelectedNode != NULL)
	{
		//Przyciski selekcji modyfikowanego obiektu/informacje
		ImGui::SetNextWindowPos(ImVec2(0, mainMenuHeight));
		ImGui::SetNextWindowSize(ImVec2(240, 480));
		ImGui::Begin("Selected node", temporaryBool, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("  Node level %i", mSelectedNode->getNodeLevel());
		//ImGui::Text("  Transform level %i", mSelectedTransform->getTransformLevel());
		if (mSelectedNode->getParentNode() != NULL && mSelectedNode->getNodeLevel() > 0 && ImGui::Button("Select parent node"))
		{
			setSelectedNode(mSelectedNode->getParentNode());
		}
		/*if (mSelectedTransform != NULL)
		{
			updateUITransformData();
		}*/

		//Pola z danymi
		ImGui::Text("Position");
		ImGui::PushID(0); //Imgui u¿ywa nazw pól jako id
		ImGui::InputFloat(":x", &mTranslateX, 0.01f, 1, 2, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat(":y", &mTranslateY, 0.01f, 1, 2, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat(":z", &mTranslateZ, 0.01f, 1, 2, ImGuiInputTextFlags_CharsDecimal);
		ImGui::PopID();
		ImGui::Text("Scale");
		ImGui::PushID(1); //Wiêc aby dalsze przyciski by³y responsywne
		ImGui::InputFloat(":x", &mScaleX, 0.1f, 1.0f, 2, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat(":y", &mScaleY, 0.1f, 1.0f, 2, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat(":z", &mScaleZ, 0.1f, 1.0f, 2, ImGuiInputTextFlags_CharsDecimal);
		ImGui::PopID();
		ImGui::Text("Rotate");
		ImGui::InputFloat(":angle", &mRotationAngle, 0.001f, 0.1f, 3, ImGuiInputTextFlags_CharsDecimal);
		ImGui::PushID(2); //U¿ywamy PushID
		ImGui::InputFloat(":x", &mRotationAxisX, 1.0f, 1.0f, 1, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat(":y", &mRotationAxisY, 1.0f, 1.0f, 1, ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat(":z", &mRotationAxisZ, 1.0f, 1.0f, 1, ImGuiInputTextFlags_CharsDecimal);
		ImGui::PopID();


		if (mSelectedTransform != NULL && ImGui::Button("Update transform")) updateTransform();
		ImGui::End();
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(0, mainMenuHeight));
		ImGui::SetNextWindowSize(ImVec2(208, 48));
		ImGui::Begin("No node selected", temporaryBool, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("  Press RMB to select node");
		ImGui::End();
	}

	ImGui::Render();
}

void UserInterface::setShouldShowInterface(const bool& pShouldShowInterface)
{
	mShouldShowInterface = pShouldShowInterface;
	if (mSelectedNode != NULL) mSelectedNode->setIsSelected(pShouldShowInterface);
}

void UserInterface::setSelectedNode(Node * const pSelectedNode)
{
	if (mSelectedNode != NULL) mSelectedNode->setIsSelected(false);
	mSelectedNode = pSelectedNode;
	mSelectedTransform = NULL;
	if (mSelectedNode != NULL)
	{
		mSelectedNode->setIsSelected(true);
		mSelectedTransform = mSelectedNode->getNodeTransform();
		updateUITransformData();
	}
}
