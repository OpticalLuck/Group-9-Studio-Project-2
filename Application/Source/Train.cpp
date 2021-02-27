#include "Train.h"

Train::Train(unsigned int id, Mesh* mesh) 
{
	SetMesh(mesh);
	SetID(id);
	SetRadius(10.f);
	SetCurrentFlag(FLAG0);
	SetObjectToLookAt(NULL);

}

Train::~Train()
{
	delete door;
	delete collisionbox;
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
	else if (getCurrentFlag() == FLAG3) {
		
	}
	else if (GetColliderBox(0)->CheckOBBCollision(lookingatobject->GetColliderBox(0)).Collided )
	{
		SetCurrentFlag(FLAG2);
	}
	
	//Flags movement



}

void Train::Init(MeshList* meshlist, GameObject* lookedAtObj)
{
	BuildMeshes(meshlist);
	lookingatobject = lookedAtObj;
}

GameObject* Train::getDoor()
{
	return door;
}

GameObject* Train::getColliderRange()
{
	return collisionbox;
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
