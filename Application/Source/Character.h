#pragma once
#include "GameObject.h"
#include "MeshList.h"
#include "CameraVer2.h"
#include "Text.h"
class Character
{
public:
	enum CHARACTER_TYPE
	{
		CHAR_AMRED = 0,
		CHAR_AMGREEN,
		CHAR_TOTAL
	};

	enum ACCESSORY_TYPE
	{
		ACC_KNIFE,
		ACC_TOTAL
	};
	Character(MeshList* meshlist);
	~Character();

	void DrawAll(Renderer* renderer, bool EnableLight);
	void Kill(CameraVer2* camera, MeshList* meshlist, double dt);
	
	void CamChange(CameraVer2 camera, Text* WorldText, Text* UI);


	GameObject* GetCharacter(CHARACTER_TYPE type);
	GameObject* GetAccessories(ACCESSORY_TYPE type);


private:
	GameObject* Accessories[ACC_TOTAL];
	GameObject* CharacterArr[CHAR_TOTAL];
	
	//for Stabby Animation
	int stabs;
	bool IsStabbed;
};

