#ifndef SCENE_TEST_H
#define SCENE_TEST_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "Text.h"
#include "UI.h"
#include "Skybox.h"

class SceneTest : public Scene
{
public:

	enum LIGHT_LOCATION
	{
		LIGHT_MIDDLE = 0,
		LIGHT_TOTAL
	};
	SceneTest();
	~SceneTest();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

private:
	double fps;
	float x_width; //sprintbar width change later
	bool mapOpen;
	Renderer* renderer;
	MeshList* meshlist;
	CameraVer2 camera;
	UI* ui;
	Skybox* skybox;
	GOManager goManager;
	GameObject* Axis;
	GameObject* Quad;
	GameObject* Item[2];
	
	Character* character;
	Text* text[5];
	Light* lights[LIGHT_TOTAL];
};

#endif