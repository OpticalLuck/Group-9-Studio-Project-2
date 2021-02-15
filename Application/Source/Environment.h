#pragma once
#include "GameObject.h"
#include "MeshList.h"

class Environment
{
public:
	enum OBJ_TYPE
	{
		OBJ_FLOOR = 0,
		OBJ_WALLS,
		OBJ_LIGHT1,
		OBJ_LIGHT2,
		OBJ_LIGHT3,
		OBJ_LIGHT4,
		OBJ_TABLE1,
		OBJ_TABLE2,
		OBJ_TABLE3,
		OBJ_TABLE4,
		OBJ_TABLE5,
		OBJ_DOORFRAME1,
		OBJ_DOORFRAME2,
		OBJ_DOORFRAME3,

		OBJ_LEVER,
		OBJ_GARBAGE,

		//Wont Render After this :D
		OBJ_BENCHUP,
		OBJ_BENCHDOWN,
		OBJ_BENCHLEFT,
		OBJ_BENCHRIGHT,
		OBJ_BTNCASE,
		OBJ_BTN,
		OBJ_DOOR1LEFT,
		OBJ_DOOR1RIGHT,
		OBJ_DOOR2LEFT,
		OBJ_DOOR2RIGHT,
		OBJ_DOOR3LEFT,
		OBJ_DOOR3RIGHT,

		TOTAL_OBJ
	};
	Environment(MeshList* meshlist);
	~Environment();
	void Draw(Renderer* renderer);
	void SetCoord(OBJ_TYPE obj, Vector3 Coord);

	void DoorInteract(OBJ_TYPE obj, bool inRange, float dt);
	void BtnInteract(GameObject* GO, double dt);

	GameObject* GetArr(OBJ_TYPE obj);
private:
	GameObject* GOArr[TOTAL_OBJ];

};