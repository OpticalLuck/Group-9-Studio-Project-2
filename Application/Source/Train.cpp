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
		if (collisionbox->GetColliderBox(0)->CheckOBBCollision(lookingatobject->GetColliderBox(0)).Collided)
		{
			std::cout << "NICE!!\n";
		}
		else {
			std::cout << "NOT!!\n";
		}
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
	door = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_TRAINDOOR));
	this->AddChild(door);
	door->SetTranslate(Vector3(1.0, 0.2, 2.4));
	door->SetColliderBox(Vector3(0.6, 0.5, 0.1));


	SetColliderBox(Vector3(0.5, 0.5, 0.1), Vector3(0, 0.2, 2.4));

	collisionbox = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_CUBE));
	//collisionbox->SetActive(false);
	this->AddChild(collisionbox);
	collisionbox->SetColliderBox(Vector3(2, 2, 2));
	collisionbox->GetColliderBox(0)->setTranslate(GetTranslate());
	Vector3 cool = collisionbox->GetColliderBox(0)->GetTranslate();
	std::cout << cool << std::endl;

}
