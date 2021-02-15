#include "Collision.h"
#include <sstream>

Collision::Collision(Vector3 position, Vector3 Size):
	position(position),
	Size(Size)
{
}

Collision::~Collision()
{
}

bool Collision::CheckCollision(Collision box1, Collision box2)
{
	return false;
}
