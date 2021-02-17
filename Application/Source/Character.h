#pragma once
#include "GameObject.h"
#include "Collision.h"
class Character : public GameObject
{ //Child of GameObject

public:
	Character(unsigned int ID, Mesh* mesh);
	~Character();

	void Init(Vector3 position = Vector3(0, 0, 0), 
			  Vector3 rotation = Vector3(0, 0, 0),
			  Vector3 scale = Vector3(1, 1, 1),
			  Vector3 CollSize = Vector3(1, 1, 1));

	void Update(double dt);

	Collision* GetCollBox();

	bool IsWithinRangeOf(GameObject* item);

private:
	Collision* CollisionBox;
};

