#pragma once
#include "CameraVer2.h"
#include "Renderer.h"
#include "MeshList.h"
#include "Character.h"
#include "Text.h"
#include "Application.h"
#include "Button.h"

class UI
{
public:
	UI();
	~UI();

	void Init(Character* player);
	void Update(double dt);
	void UpdateInteractions(GameObject* item);
	
	void Draw(Renderer* renderer, bool enableLight = false);
	
	void Exit();

	GameObject* getItem();
	bool getInteractable();
	float getMapBoundsX();
	float getMapBoundsZ();

	void setCamera(CameraVer2* camera);
	void setItem(GameObject* item);
	void setInteractable(bool interactable);
	void setMapBounds(float max_X, float max_Z);

private:
	CameraVer2* camera;
	Character* Player;
	GameObject* Quad;
	GameObject* Item; //TODO: Make Item its own class instead of a GO
	GameObject* PauseBG;
	Button* PauseButton[3];

	Mesh* BG;
	Text* Info[10];
	Text* Quests[10];
	Text* text[400];

	float staminaBar_width;
	float max_X, max_Z;
	int Button_Count;

	bool KeyPressed;
	bool isMousePressed;
	bool isEscPressed;
	bool interactable;
	bool text2active;
	bool bPause;
	bool bTab;
	bool Dialogue;
	bool Dialogue_1 = false;
	bool Dialogue_2 = false;
	bool Dialogue_3 = false;
	bool Dialogue_4 = true;
};