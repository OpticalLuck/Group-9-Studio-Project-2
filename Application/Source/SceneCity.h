#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

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
#include "NPC.h"
#include "Train.h"
#include "WayPoint.h"

class SceneCity : public Scene
{
public:
	enum Environment_Type
	{
		EN_FLOOR = 0,
		EN_GATE,
		EN_HOUSE1,
		EN_HOUSE2,
		EN_HOUSE3,
		EN_HOUSE4,
		EN_HOUSE5,
		EN_STADIUM,
		EN_SCHOOL,
		EN_FANCYHOUSE,
		EN_PAGODA,
		EN_TREE,
		EN_TOTAL
	};

	enum NPCLOCATION //USE FOR NPC ID AND IDEA OF WHERE IT SPAWNS
	{
		TRAIN_BUSY1,
		TRAIN_BUSY2,
		LIBRARY_BUSY1,
		LIBRARY_REST,

		NPC_TOTAL
	};


	enum LIGHT_LOCATION
	{
		LIGHT_SUN,
		LIGHT_TOTAL
	};

	enum WP_TYPE //USED TO SET EMPTY GAMEOBJECTS (NOMESH) as way points for us to see where we can change scenes
	{
		WP_STADIUM,
		WP_HALL,
		WP_LIBRARY,
		WP_TRAIN,
		WP_TOTAL
	};
	SceneCity();
	~SceneCity();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

	//virtual static bool bPauseGame; //Used for pausing
private:
	double fps;

	Renderer* renderer;

	CameraVer2 camera;

	GOManager goManager;
	GameObject* Axis;
	Character* Ayaka;
	NPC* npc[NPC_TOTAL];
	GameObject* Environment[EN_TOTAL];
	GameObject* Boost;
	GameObject* Collectible;
	WayPoint* Waypoints[WP_TOTAL]; //For a switching scenes
	Light* lights[LIGHT_TOTAL];
	Skybox* skybox;
	UI* ui;
	//Temp
	GameObject* Cube[4];
	Train* train;
	GameObject* traincollider;

	void GenerateNPCs(MeshList* meshlist);
	void UpdateNPCs(double dt);
	void DrawNPCs();
	void SetTrainPath();
};

#endif