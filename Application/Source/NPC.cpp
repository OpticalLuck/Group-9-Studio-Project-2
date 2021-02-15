#include "NPC.h"



NPC::NPC(unsigned int id, Mesh* mesh)
{
	SetMesh(mesh);

	//init(meshlist* meshlist);
	BodyArr[HEAD] = new GameObject(GetID(), meshlist.GetMesh(MeshList::MESH_HEAD));
	AddChild(BodyArr[HEAD]);

	//BodyArr[HEAD]->SetRotate();
}

NPC::~NPC()
{
}
