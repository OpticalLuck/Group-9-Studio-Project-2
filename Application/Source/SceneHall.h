#ifndef SCENE_HALL_H
#define SCENE_HALL_H

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

class SceneHall : public Scene
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
		EN_TABLE,
		EN_PLANT1,
		EN_PLANT2,
		EN_PLANT3,
		EN_PLANT4,
		EN_TOTAL
	};

	enum LIGHT_LOCATION
	{
		LIGHT_MIDDLE,
		LIGHT_TEST,
		LIGHT_TOTAL
	};
	SceneHall();
	~SceneHall();

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
	NPC* npc;
	GameObject* Environment[EN_TOTAL];
	Light* lights[LIGHT_TOTAL];
	Skybox* skybox;

	//Temp
	GameObject* Cube[2];
};

#endif