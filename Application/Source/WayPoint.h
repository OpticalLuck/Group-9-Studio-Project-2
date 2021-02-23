#pragma once
#include "GameObject.h"
#include "Text.h"
class WayPoint : public GameObject
{
public:
	WayPoint(std::string name, Vector3 position);
	~WayPoint();

	void Draw(Renderer* renderer, bool enablelight) override;

	//Response if target e.g. u are close to waypoint
	void inRangeResponse(GameObject* Target);

	bool getisInRange();
private:
	Text* OnScreenText;
	bool isInRange;
};

