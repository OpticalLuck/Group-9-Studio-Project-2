#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "Skybox.h"
#include "TextureList.h"
#include "Text.h"
#include "UI.h"
#include "WayPoint.h"

class SceneStadium : public Scene
{
public:
	enum Environment_Type
	{
		EN_FLOOR = 0,
		EN_TOTAL
	};

	SceneStadium();
	~SceneStadium();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

	int getRingCount();

private:
	double fps;
	Renderer* renderer;

	CameraVer2 camera;

	GOManager goManager;
	GameObject* Axis;
	Character* Ayaka;
	GameObject* Environment[EN_TOTAL];
	GameObject* Boost[2];
	GameObject* Rings[16];
	GameObject* Collectible;
	WayPoint* Waypoint; //For a switching scenes

	Light* lights[4];
	Skybox* skybox;
	Text* instructions;
	UI* ui;

	int RingCollected, maxRing;
};

