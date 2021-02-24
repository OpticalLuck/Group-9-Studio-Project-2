#pragma once
#include "CameraVer2.h"
#include "Renderer.h"
#include "MeshList.h"
#include "Character.h"
#include "Text.h"

class UI
{
public:
	UI();
	~UI();

	void Init(Character* player);
	void Update();
	void UpdateInteractions(GameObject* item);
	
	void Draw(Renderer* renderer, bool enableLight);
	
	void Exit();

	GameObject* getItem();
	MeshList* getMeshList();
	bool getInteractable();

	void setCamera(CameraVer2* camera);
	void setItem(GameObject* item);
	void setInteractable(bool interactable);
	void setMeshList(MeshList* meshlist);
private:
	CameraVer2* camera;
	MeshList* meshlist;
	Character* Player;
	GameObject* Quad;
	GameObject* Item; //TODO: Make Item its own class instead of a GO

	Text* text[400];

	float staminaBar_width;
	bool interactable;
	bool text2active;
	bool text3active;
	bool mapOpen;
	bool Dialogue;
};