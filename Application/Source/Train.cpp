#include "Train.h"

Train::Train(unsigned int id, Mesh* mesh) 
{
	SetMesh(mesh);
	SetID(id);
	SetRadius(10.f);
	SetCurrentFlag(FLAG0);
	objectToLookAt = NULL;
	door = NULL;
	nextstop = 0;
	dt = 0;
}

Train::~Train()
{
	delete door;

}

void Train::Update(double dt)
{
	this->dt = dt;
	if (getCurrentFlag() == FLAG2) { //close the doors
		if (door->GetTranslate().x < 1.0) {
			door->SetTranslate(Vector3(door->GetTranslate().x + 2 * dt, 0.2, 2.4));
			GetColliderBox(1)->setOffsetpos(door->GetTranslate() + Vector3(0,1,0));
		}
		else if (door->GetTranslate().x >= 1.0) {
			door->SetTranslate(Vector3(1.0, 0.2, 2.4));
			GetColliderBox(1)->setOffsetpos(door->GetTranslate() + Vector3(0, 1, 0));

			SetCurrentFlag(FLAG3);

		}
		
	}
	else if (getCurrentFlag() == FLAG3 && !stops.empty() && nextstop < static_cast<int>(stops.size())) { //train movement
		float speed = 10.f * dt;
		velocity += Math::Clamp(speed, 0.f, 20.f);
		Vector3 velocitydir = (stops.at(nextstop) - GetTranslate()).Normalized();

		MoveToPos(stops.at(nextstop), velocity);
		/*float angleToPoint = GetAngleToPoint(stops.at(nextstop));
		float offsetangle = 0.9f;
		float ROTATIONSPEED = 2 * dt;
		float rotationval;

		rotationval = (1 - ROTATIONSPEED) * GetRotate().y + ROTATIONSPEED * angleToPoint;
		if (GetRotate().y > 360)
		{
			rotationval -= 360;
		}
		else if (GetRotate().y < 0)
		{
			rotationval += 360;
		}
		SetRotate(Vector3(0, rotationval, 0));*/
		objectToLookAt->SetTranslate(objectToLookAt->GetTranslate() + velocitydir * velocity * dt);
		

		if (abs((GetTranslate() - stops.at(nextstop)).Length()) < 1) {
			nextstop++;
		}

	}
	else if (GetColliderBox(0)->CheckOBBCollision(objectToLookAt->GetColliderBox(0)).Collided )
	{
		SetCurrentFlag(FLAG2);
	}
	
	//Flags movement



}

void Train::Init(MeshList* meshlist, GameObject* lookedAtObj)
{
	BuildMeshes(meshlist);
	objectToLookAt = lookedAtObj;
}

void Train::PushStop(Vector3 dest)
{
	stops.push_back(dest);
}

void Train::PushStop(float x, float y, float z)
{
	PushStop(Vector3(x, y, z));
}





void Train::BuildMeshes(MeshList* meshlist)
{
	Vector3 cool; //for debugging

	SetColliderBox(Vector3(4.5, 0.1, 3)); 
	
	
	door = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_TRAINDOOR));
	door->SetTranslate(Vector3(-1.8, 0.2, 2.4));
	this->AddChild(door);
	SetColliderBox(Vector3(1.75, 1.25, 0), door->GetTranslate() + Vector3(0,1,0)); //door collider (idx 1)
	
	
	SetColliderBox(Vector3(2, 1.2, 0.2), Vector3(-2.45, 1, 2.7));

	SetColliderBox(Vector3(0.9, 1.2, 0.2), Vector3(3.5, 1, 2.7));





}
