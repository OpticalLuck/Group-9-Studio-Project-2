#pragma once
#include "CameraVer2.h"
#include "Renderer.h"
#include "MeshList.h"
#include "GameObject.h"
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
	bool getNPCstate();
	bool getIsNearNPC();

	void setItem(GameObject* item);
	void setInteractable(bool interactable);
	void setMapBounds(float max_X, float max_Z);
	void setNPCText(std::vector<std::string> *speechstring); //only set when npc is interacted with!
	void setIsNearNPC(bool yn);

private:
	CameraVer2* camera;
	Character* Player;
	GameObject* Quad;
	GameObject* Item; //TODO: Make Item its own class instead of a GO
	GameObject* PauseBG;
	GameObject* ControlsPage;
	Button* PauseButton[4];

	Mesh* BG;
	Text* Info[10];
	Text* Quests[10];
	Text* text[101];
	std::vector<Text*> NPC_Text;

	float staminaBar_width;
	float max_X, max_Z;
	int Button_Count;

	bool KeyPressed;
	bool isMousePressed;
	bool isEscPressed;
	bool interactable;
	bool text2active;
	bool bPause;
	bool bControlMenu;
	bool bTab;
	bool Dialogue;
	bool NPCDialogue;
	bool isNearNPC;
	bool Dialogue_1 = true;
	bool Dialogue_2 = false;
	bool Dialogue_3 = false;
	bool Dialogue_4 = false;
	bool Quest_1 = false; //Meet the City Mayor in City Hall
	bool Quest_2 = false; //Collect the 3 Gems
	bool Quest_3 = false; //Head back over to City Hall
	bool Quest_4 = false; //Enter the portal & return home.


	void DrawNPCText(Renderer* renderer);
};