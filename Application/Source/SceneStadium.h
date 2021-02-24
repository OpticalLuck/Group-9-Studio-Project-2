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

	enum LIGHT_LOCATION
	{
		LIGHT_MIDDLE,
		LIGHT_TOTAL
	};

	enum TEXT_TYPE
	{
		TEXT_FPS,
		TEXT_POSITION,
		TEXT_TOTAL
	};

	SceneStadium();
	~SceneStadium();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

private:
	double fps;
	Renderer* renderer;

	CameraVer2 camera;

	GOManager goManager;
	GameObject* Axis;
	Character* Ayaka;
	GameObject* Environment[EN_TOTAL];
	//GameObject* Rings[R_TOTAL];
	WayPoint* Waypoint; //For a switching scenes

	Light* lights[LIGHT_TOTAL];
	Skybox* skybox;
	Text* textarr[TEXT_TOTAL];
	UI* ui;

};

