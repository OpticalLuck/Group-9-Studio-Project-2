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
	float x_width;
	bool mapOpen;
	Renderer* renderer;
	MeshList* meshlist;
	CameraVer2 camera;

	GOManager goManager;
	GameObject* Axis;
	GameObject* Quad;
	GameObject* Item[2];
	GameObject* Skybox_Top;
	GameObject* Skybox_Bottom;
	GameObject* Skybox_Left;
	GameObject* Skybox_Right;
	GameObject* Skybox_Front;
	GameObject* Skybox_Back;
	Character* character;
	Text* text[5];
	Light* lights[1];
};

#endif