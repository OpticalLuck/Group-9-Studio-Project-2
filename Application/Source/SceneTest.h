#ifndef SCENE_TEST_H
#define SCENE_TEST_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "Text.h"

class SceneTest : public Scene
{
public:
	SceneTest();
	~SceneTest();

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
	Character* NPC;
	Text* text;
	Light* lights[1];
};

#endif