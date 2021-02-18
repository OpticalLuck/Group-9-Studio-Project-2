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

	collectibleCount = 0;
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

bool Character::IsWithinRangeOf(GameObject* item)
{
	//getTranslate() by itself access the position of Character, while item->GetTranslate() access the position of the item parameter that is passed in
	if (GetInRange(item,10))
	{
		item->SetCurrentFlag(FLAG1);
		return true;
	}
	item->SetCurrentFlag(FLAG0);
	return false;
}

int Character::getCollectibleCount()
{
	return collectibleCount;
}

void Character::IncrementCollectible()
{
	collectibleCount += 1;
}