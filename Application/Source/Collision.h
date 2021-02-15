#pragma once
#include "Vector3.h"
#include "Mtx44.h"

class Collision
{
public:

	Collision(Vector3 position, Vector3 Size);
	~Collision();

	bool CheckCollision(Collision box1, Collision box2);
private:

	Vector3 position;
	Vector3 Size;
};

