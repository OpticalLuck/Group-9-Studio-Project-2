#ifndef SCENE_LIBRARY_H
#define SCENE_LIBRARY_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "Skybox.h"
#include "TextureList.h"
#include "UI.h"
#include "NPC.h"
#include "WayPoint.h"

class SceneLibrary : public Scene
{
public:

	enum Environment_Type
	{
		EN_FLOOR1 = 0,
		EN_FLOOR2,
		EN_FLOOR3,
		EN_FLOOR4,
		EN_FLOOR5,
		EN_FLOOR6,
		EN_COUNTER,
		EN_TABLE1,
		EN_TABLE2,
		EN_TABLE3,
		EN_TABLE4,
		EN_PLANT1,
		EN_PLANT2,
		EN_TOTAL
	};

	enum LIGHT_LOCATION
	{
		LIGHT_MIDDLE,
		LIGHT_TEST,
		LIGHT_TOTAL
	};

	enum WP_TYPE
	{
		WP_DOOR,
		WP_TOTAL
	};
	SceneLibrary();
	~SceneLibrary();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

private:
	double fps;

	Renderer* renderer;

	TextureList* texturelist;
	MeshList* meshlist;
	CameraVer2 camera;
	UI* ui;
	GOManager goManager;
	GameObject* Axis;
	Character* MainChar;
	Character* Ayaka;
	GameObject* Environment[EN_TOTAL];
	GameObject* Collectible;
	WayPoint* Waypoints[WP_TOTAL];
	Light* lights[LIGHT_TOTAL];
	Skybox* skybox;
	NPC* npc;
	Text* Character_Name[1];

	//Temp
	GameObject* Cube[2];
};

#endif