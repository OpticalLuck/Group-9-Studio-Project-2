#ifndef SCENE_TRAIN_H
#define SCENE_TRAIN_H

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
#include "Train.h"
#include "WayPoint.h"

class SceneTrain : public Scene
{
public:

	enum Environment_Type
	{
		EN_FLOOR1 = 0,
		EN_HOUSE1,
		EN_HOUSE2,
		EN_HOUSE3,
		EN_PLATFORM,
		EN_TRAINSTATION,
		EN_TOWER,
		//TREES
		EN_TREE,
		EN_TREEBOTL1,
		EN_TREEBOTL2,
		EN_TREEBOTL3,
		EN_TREEBOTR1,
		EN_TREEBOTR2,
		EN_TREEBOTR3,
		EN_TREETOPR1,
		EN_TREETOPR2,
		EN_TREETOPR3,
		EN_TREETOPL1,
		EN_TREETOPL2,
		EN_TREETOPL3,
		EN_ENDTREES,


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

	SceneTrain();
	~SceneTrain();

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
	UI* ui;
	GOManager goManager;
	GameObject* Axis;
	Character* Ayaka;
	GameObject* Environment[EN_TOTAL];
	Train* train;
	GameObject* traincollider;
	Light* lights[LIGHT_TOTAL];
	Skybox* skybox;
	NPC* npc;
	WayPoint* Waypoints[WP_TOTAL];
};

#endif