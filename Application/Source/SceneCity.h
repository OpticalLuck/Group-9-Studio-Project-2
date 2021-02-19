#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"
#include "Skybox.h"

class SceneCity : public Scene
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
		LIGHT_TEST,
		LIGHT_TOTAL
	};
	SceneCity();
	~SceneCity();

	virtual void Init();
	virtual void InitGL();
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
	Character* MainChar;
	GameObject* Environment[EN_TOTAL];
	Light* lights[LIGHT_TOTAL];
	Skybox* skybox;

	//Temp
	GameObject* Cube[2];
};

#endif