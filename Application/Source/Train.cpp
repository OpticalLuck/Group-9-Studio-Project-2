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
}

void Train::Update(double dt)
{
}

void Train::Init(MeshList* meshlist, GameObject* lookedAtObj)
{
	BuildMeshes(meshlist);
}

void Train::BuildMeshes(MeshList* meshlist)
{

}
