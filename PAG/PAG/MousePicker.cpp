#include "MousePicker.hpp"
#include "Model.hpp"
#include "Scene.hpp"
#include "Node.hpp"
#include <glm/gtx/matrix_decompose.hpp>

glm::vec3 MousePicker::calculateMouseRay(float mouseX, float mouseY)
{
	float x = (2.0f*mouseX) / SCREEN_WIDTH - 1.0f;
	float y = (2.0f*mouseY) / SCREEN_HEIGHT - 1.0f;

	glm::vec4 clipCoords = glm::vec4(x, y, -1.0f, 1.0f);

	glm::mat4 inversedProjection = glm::inverse(projectionMatrix);
	glm::vec4 eyeCoords = inversedProjection * clipCoords;

	glm::mat4 inversedView = glm::inverse(viewMatrix);
	glm::vec4 rayWorld = inversedView * eyeCoords;
	glm::vec3 worldRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	worldRay = glm::normalize(worldRay);
	return worldRay;
}

glm::vec3 MousePicker::getCurrentRay()
{
	return currentRay;
}

void MousePicker::update(float mouseX, float mouseY)
{
	this->viewMatrix = camera->getViewMatrix();
	currentRay = calculateMouseRay(mouseX, mouseY);
}

MousePicker::MousePicker()
{
}

MousePicker::MousePicker(Camera& camera, glm::mat4 projection)
{
	this->camera = std::make_shared<Camera>(camera);
	this->projectionMatrix = projection;
	this->viewMatrix = camera.getViewMatrix();
}


MousePicker::~MousePicker()
{
}

glm::vec3 MousePicker::getPointOnRay(glm::vec3 ray, float distance) {
	glm::vec3 camPos = camera->cameraPos;
	glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
	glm::vec3 scaledRay = glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
	return start + scaledRay;
}

Node * MousePicker::getSelectedNode(Scene *const pScene, Model* model, const std::pair<int, int>& pScreenSize, const std::pair<double, double>& pMousePos)
{
	int i;
	glm::vec4 rayStartPoint(
		(2.0f*pMousePos.first) / pScreenSize.first - 1.0f, //Normalizacja szerokoœci
		1.0f - ((2.0f*pMousePos.second) / pScreenSize.second), //Normalizacja wysokoœci
		-1.0f, 1.0f); //-1.0 w znormalizowanej postaci to plan bliski
	glm::vec4 rayEndPoint(
		(2.0f*pMousePos.first) / pScreenSize.first - 1.0f, //Normalizacja szerokoœci
		1.0f - ((2.0f*pMousePos.second) / pScreenSize.second), //Normalizacja wysokoœci
		1.0f, 1.0f); //1.0 w znormalizowanej postaci to plan daleki

					 //Odwrotne transformacje przez macierze œwiata
	glm::mat4 inverseVP = glm::inverse(pScene->getProjectionSpace()*pScene->getViewSpace());

	//Obliczanie punktów w œwiecie
	glm::vec4 rayStartPointWorld = inverseVP*rayStartPoint;
	rayStartPointWorld /= rayStartPointWorld.w;
	glm::vec4 rayEndPointWorld = inverseVP*rayEndPoint;
	rayEndPointWorld /= rayEndPointWorld.w;

	//Obliczanie kierunku promienia
	glm::vec3 rayDirectionWorld(rayEndPointWorld - rayStartPointWorld);
	rayDirectionWorld = glm::normalize(rayDirectionWorld);

	//Obliczanie najbli¿szego Node
	std::vector<std::pair<Node*, float>> intersectedNodes;
	/*intersectedNodes.push_back(model->testRayOBBIntersection(rayStartPointWorld, rayDirectionWorld));
	if (intersectedNodes.size() == 0) return NULL;*/


	auto allNodes = model->getAllNodes();

	for (int i = 0; i < allNodes.size(); i++) {
		auto intersection = allNodes.at(i)->tryGetIntersection(rayStartPointWorld, rayDirectionWorld);
		if (intersection.first) {
			intersectedNodes.push_back(std::pair<Node*, float>(allNodes.at(i), intersection.second));
		}
	}
	if (intersectedNodes.size() == 0) return NULL;
	//intersectedNodes.at(5).second = -10.0f;

	std::pair<Node*, float> closestNode = intersectedNodes[0];
	for (i = 1; i<intersectedNodes.size(); i++)
	if (intersectedNodes[i].second<closestNode.second) closestNode = intersectedNodes[i];
	return closestNode.first;
}

const bool MousePicker::checkRayIntersectionTriangle(const glm::vec3& pRaySource, const glm::vec3& pRayDirection, const glm::vec3 triangle[3], float& pDistanceOutput)
{
	const float epsilon = 0.00000001;
	glm::vec3 edge1, edge2, h, s, q;
	float a, f, u, v, t;

	//Obliczanie krawêdzi
	edge1 = triangle[1] - triangle[0];
	edge2 = triangle[2] - triangle[0];
	h = glm::cross(pRayDirection, edge2);
	a = glm::dot(edge1, h);
	if (fabs(a) < epsilon)
		return false;
	f = 1 / a;
	s = pRaySource - triangle[0];
	u = f*glm::dot(s, h);
	if (u<0.0 || u>1.0)
		return false;
	q = glm::cross(s, edge1);
	v = f*glm::dot(pRayDirection, q);
	if (v<0.0 || (u + v)>1.0)
		return false;
	t = f*glm::dot(edge2, q);
	if (t > epsilon)
	{
		pDistanceOutput = glm::distance(pRaySource, pRaySource + (pRayDirection*t));
		return true;
	}
	else
		return false;
}
