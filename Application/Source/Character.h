#pragma once
#include "GameObject.h"
#include "Collision.h"
class Character : public GameObject
{
public:
	Character(unsigned int ID, Mesh* mesh);
	~Character();

	void Init(Vector3 position, Vector3 halfsize);
	void Update(double dt);

	Collision* GetCollBox();
private:
	Collision* CollisionBox;
};

