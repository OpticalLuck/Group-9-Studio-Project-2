#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "Character.h"
#include "SkyBox.h"
#include "Environment.h"
#include "Text.h"
#include "A1FG.h"

class SceneText : public Scene
{
public:

	enum KnifeANi
	{
		In,
		Out,
		None
	};
	SceneText();
	~SceneText();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(float xoffset, float yoffset) override;

private:
	float fps;
	Renderer* renderer;
	MeshList* meshlist;
	GameObject* Axis;
	SkyBox* skybox;
	Environment* environment;
	Text* text[6];
	A1FG* FallGuys;
	Character* Characters;
	CameraVer2 camera2;
	Light* lights[4];
};

#endif