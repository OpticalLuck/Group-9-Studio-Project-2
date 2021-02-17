#include "MeshList.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
MeshList::MeshList()
{
	meshlist[MESH_AXIS] = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);

	meshlist[MESH_QUAD] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));

	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);

	meshlist[MESH_STAMINABAR] = MeshBuilder::GenerateCube("Cube", Color(0.f, 1.f, 0.f), 1.f, 1.f, 1.f);

	meshlist[MESH_ICON] = MeshBuilder::GenerateQuad("Icon", Color(1.f, 0.f, 0.f), 1.0f);

	meshlist[MESH_HEAD] = MeshBuilder::GenerateCube("Head", Color(1.f,1.f,0.f), 1.f, 1.f, 1.f);

	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f,1.f,1.f), 1.f, 1.f, 1.f);
}

MeshList::~MeshList()
{
}

Mesh* MeshList::GetMesh(MESH_TYPE meshtype)
{
	return meshlist[meshtype];
}

