#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Renderer.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Light.h"
#include "GameObject.h"

class SceneA2 : public Scene
{
public:
	enum Text_Type
	{
		ButtonInteract,
		World_KillGreen,
		Screen_KillGreen,
		ImposterText,
		Lever,
		UI,
		TEXT_TOTAL
	};
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
	GameObject * Axis;
	CameraVer2 camera;
	Light* lights[4];
};

#endif