#pragma once
#include "GameObject.h"
#include "Text.h"
#include "SceneManager.h"
class WayPoint : public GameObject
{
public:
	WayPoint(std::string name, Vector3 position);
	~WayPoint();

	void Draw(Renderer* renderer, bool enablelight = false) override;
	void DrawLocName(Renderer* renderer);
	//Response if target e.g. u are close to waypoint
	bool inRangeResponse(GameObject* Target, SceneManager::SCENE_TYPE NextScene);

	std::string getLocation();
private:
	Text* OnScreenText;
	std::string name;
	bool isInRange, isEPressed;
};

