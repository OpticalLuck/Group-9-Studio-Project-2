#pragma once
#include "MeshList.h"
#include "GameObject.h"
#include "GOManager.h"

class Skybox
{
public:
	enum SKYBOX_FACE
	{
		SBX_FRONT = 0,
		SBX_BACK,
		SBX_LEFT,
		SBX_RIGHT,
		SBX_TOP,
		SBX_BOTTOM,
		SBX_TOTAL
	};

	Skybox(GOManager gomanager, MeshList* meshlist);
	~Skybox();

	GameObject* GetSBX(int idx);
private:
	GameObject* SB_ARR[SBX_TOTAL];

};

