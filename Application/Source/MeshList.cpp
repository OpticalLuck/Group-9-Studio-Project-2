#include "MeshList.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
MeshList::MeshList()
{
	//// <PRIMATIVES> 
	meshlist[MESH_AXIS] = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);

	meshlist[MESH_QUAD] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));

	meshlist[MESH_FLOOR] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));
	meshlist[MESH_FLOOR]->textureID = LoadTGA("Image//Floor.tga");
	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	//// </PRIMATIVES> 

	//// <UI> 
	meshlist[MESH_STAMINABAR] = MeshBuilder::GenerateCube("Cube", Color(0.f, 1.f, 0.f), 1.f, 1.f, 1.f);

	meshlist[MESH_ICON] = MeshBuilder::GenerateQuad("Icon", Color(1.f, 0.f, 0.f), 1.0f);
	//// </UI> 

	//// <NPC> 
	meshlist[MESH_HEAD] = MeshBuilder::GenerateCube("Head", Color(1.f,1.f,0.f), 1.f, 1.f, 1.f);
	//// </NPC> 
	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f,1.f,1.f), 1.f, 1.f, 1.f);

	////Skybox
	meshlist[SKYBOX_FRONT] = MeshBuilder::GenerateQuad("Front of Skybox", Color(1, 1, 1), 50.0f);
	meshlist[SKYBOX_FRONT]->textureID = LoadTGA("Image//miramar_ft.tga");

	meshlist[SKYBOX_BACK] = MeshBuilder::GenerateQuad("Back of Skybox", Color(1, 1, 1), 50.0f);
	meshlist[SKYBOX_BACK]->textureID = LoadTGA("Image//miramar_bk.tga");

	meshlist[SKYBOX_TOP] = MeshBuilder::GenerateQuad("Top of Skybox", Color(1, 1, 1), 50.0f);
	meshlist[SKYBOX_TOP]->textureID = LoadTGA("Image//miramar_up.tga");

	meshlist[SKYBOX_BOTTOM] = MeshBuilder::GenerateQuad("Bottom of Skybox", Color(1, 1, 1), 50.1f);
	meshlist[SKYBOX_BOTTOM]->textureID = LoadTGA("Image//miramar_dn.tga");

	meshlist[SKYBOX_LEFT] = MeshBuilder::GenerateQuad("Left of Skybox", Color(1, 1, 1), 50.0f);
	meshlist[SKYBOX_LEFT]->textureID = LoadTGA("Image//miramar_lf.tga");

	meshlist[SKYBOX_RIGHT] = MeshBuilder::GenerateQuad("Right of Skybox", Color(1, 1, 1), 50.0f);
	meshlist[SKYBOX_RIGHT]->textureID = LoadTGA("Image//miramar_rt.tga");
}

MeshList::~MeshList()
{
}

Mesh* MeshList::GetMesh(MESH_TYPE meshtype)
{
	return meshlist[meshtype];
}

