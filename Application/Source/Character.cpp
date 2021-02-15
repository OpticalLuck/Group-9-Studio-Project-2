#include "Character.h"

Character::Character(unsigned int ID, Mesh* mesh)
{
	SetID(ID);
	SetMesh(mesh);
}

Character::~Character()
{
}

void Character::Init(Vector3 position, Vector3 halfsize)
{
	SetTranslate(position);
	CollisionBox = new Collision(position, halfsize);
}

void Character::Update(double dt)
{
	CollisionBox->setcollpos(GetTranslate());
}

Collision* Character::GetCollBox()
{
	return CollisionBox;
}
