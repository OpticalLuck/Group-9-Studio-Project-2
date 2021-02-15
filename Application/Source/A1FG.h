#pragma once
#include "GameObject.h"
#include "Text.h"
class A1FG : public GameObject
{
public:
	enum BODY_PARTS
	{
		TOP_BODY,
		BODY,
		BOTTOM_BODY,
		FACE,
		EYE,
		
		SHOULDER,
		ELBOW,
		UPPER_ARM,
		LOWER_ARM,

		LEG,
		FEET,

		TOTAL_PARTS
	};

	A1FG();
	~A1FG();

	void Draw(Renderer* renderer, bool enablelight) override;
	void EjectInteract(CameraVer2* camera, Text* text, double dt);

private:
	Mesh* BodyArr[TOTAL_PARTS];
};

