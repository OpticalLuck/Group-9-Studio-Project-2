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

	void Init(GameObject* player);
	void Update();
	void UpdateInteractions(GameObject* item);
	
	void Draw(Renderer* renderer, bool enableLight);
	
	void Exit();

	bool getCamSprintState();
	GameObject* getItem();
	MeshList* getMeshList();

	void setCamera(CameraVer2* camera);
	void setCamSprintState(bool isSprinting);
	void setItem(GameObject* item);
	void setInteractable(bool interactable);
	void setMeshList(MeshList* meshlist);
private:
	CameraVer2* camera;
	MeshList* meshlist;
	GameObject* Quad;
	GameObject* Player;
	GameObject* Item; //TODO: Make Item its own class instead of a GO

	Text* text[3];

	float staminaBar_width;
	bool interactable;
	bool text2active;
	bool text3active;
	bool mapOpen;
};