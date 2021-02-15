#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GOManager.h"

class SceneA2 : public Scene
{
public:
	SceneA2();
	~SceneA2();

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
	Light* lights[1];
};

#endif