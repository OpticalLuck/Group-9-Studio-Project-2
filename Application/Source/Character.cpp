#include "Character.h"
#include "Application.h"

int Character::collectibleCount = 0;
Character::Character(unsigned int ID, Mesh* mesh)
{
	SetID(ID);
	SetMesh(mesh);
	camera = NULL;
	charspeed = 15.f;
	dt = 0;
}

Character::~Character()
{
}

void Character::Init(Vector3 position, Vector3 rotation, Vector3 scale)
{
	SetTranslate(position);
	SetRotate(rotation);
	SetScale(scale);

	//collectibleCount = 0;
}

void Character::Update(double dt)
{
	this->dt = dt;


	Vector3 view = camera->GetView();
	view.y = 0;
	view.Normalize();
	Vector3 pos = camera->GetPosition();
	Vector3 target = view + pos;
	Vector3 right = camera->GetRight();
	right.y = 0;
	right.Normalize();

	Vector3 newpos, newrot;
	newpos = GetTranslate();
	newrot = GetRotate();

	if (Application::IsKeyPressed('W')) {
		newpos = newpos + view * charspeed * dt;
	}
	
	if (Application::IsKeyPressed('A')) {
		newpos = newpos - right * charspeed * dt;
	}
	
	if (Application::IsKeyPressed('S')) {
		newpos = newpos - view * charspeed * dt;
	}
	
	if (Application::IsKeyPressed('D')) {
		newpos = newpos + right * charspeed * dt;
	}
	
	SetTranslate(newpos);

	camera->SetPosition(newpos);
	camera->SetTarget(view + newpos);

}




bool Character::IsWithinRangeOf(GameObject* item)
{
	//getTranslate() by itself access the position of Character, while item->GetTranslate() access the position of the item parameter that is passed in
	if (GetInRange(item,item->GetRadius()))
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

void Character::SetCamera(CameraVer2* camera)
{
	this->camera = camera;
}
