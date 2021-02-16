#ifndef SCENE_NPCTEST_H
#define SCENE_NPCTEST_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "NPC.h"

class SceneNPCTest : public Scene
{
public:
	SceneNPCTest();
	~SceneNPCTest();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

private:
	double fps;
	Renderer* renderer;
	MeshList* meshlist;
	CameraVer2 camera;

	GOManager goManager;
	GameObject* Axis;
	GameObject* Quad;
	Character* MainCharacter;
	NPC* npc;
	Light* lights[1];
};

#endif