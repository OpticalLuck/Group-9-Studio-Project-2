#ifndef SCENE_NPCTEST_H
#define SCENE_NPCTEST_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "Skybox.h"
#include "TextureList.h"
#include "NPC.h"

class SceneNPCTest : public Scene
{
public:

	enum LIGHT_LOCATION
	{
		LIGHT_MIDDLE = 0,
		LIGHT_TOTAL
	};
	SceneNPCTest();
	~SceneNPCTest();

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

	GOManager goManager;
	GameObject* Axis;
	GameObject* Quad;
	Character* MainCharacter;
	NPC* npc;
	Light* lights[LIGHT_TOTAL];
};

#endif