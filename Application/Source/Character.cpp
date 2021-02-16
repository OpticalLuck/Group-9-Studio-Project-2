#include "Character.h"

Character::Character(unsigned int ID, Mesh* mesh)
{
	SetID(ID);
	SetMesh(mesh);
}

Character::~Character()
{
}

void Character::Init(Vector3 position, Vector3 rotation, Vector3 scale, Vector3 CollSize)
{
	SetTranslate(position);
	SetRotate(rotation);
	SetScale(scale);
	CollisionBox = new Collision(position, CollSize * 0.5f);
}

void Character::Update(double dt)
{
	CollisionBox->setcollpos(GetTranslate());
	CollisionBox->setRotation(GetRotate().x, GetRotate().y, GetRotate().z);
}

Collision* Character::GetCollBox()
{
	return CollisionBox;
}
