#pragma once
#include "CameraVer2.h"
#include "Renderer.h"
#include "MeshList.h"
#include "Text.h"

class UI
{
public:
	UI();
	~UI();

	void Init();
	void Update();
	
	void Draw(Renderer* renderer, bool enableLight);
	
	void Exit();

	bool getCamSprintState();

	void setCamera(CameraVer2* camera);
	void setCamSprintState(bool isSprinting);
private:
	CameraVer2* camera;
	MeshList* tempMeshList;
	GameObject* Quad;
	Text* text[4];

	float staminaBar_width;
	//bool camSprintState;
};