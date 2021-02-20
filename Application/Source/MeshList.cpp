#include "MeshList.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
MeshList::MeshList()
{
	//// <PRIMATIVES> 
	meshlist[MESH_AXIS] = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);
	meshlist[MESH_QUAD] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));
	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	//// </PRIMATIVES> 
	
	meshlist[MESH_FLOOR] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));
	meshlist[MESH_FLOOR]->textureArr[0] = LoadTGA("Image//Floor.tga");

	meshlist[MESH_HOUSE1] = MeshBuilder::GenerateOBJMTL("House_1", "OBJ//House1.obj", "OBJ//House1.mtl");
	//meshlist[MESH_HOUSE1]->textureArr[0] = LoadTGA("Image//House1.tga");

	meshlist[MESH_HOUSE2] = MeshBuilder::GenerateOBJMTL("House_2", "OBJ//House2.obj", "OBJ//House2.mtl");
	//meshlist[MESH_HOUSE2]->textureArr[0] = LoadTGA("Image//House2.tga");

	meshlist[MESH_HOUSE3] = MeshBuilder::GenerateOBJMTL("House_3", "OBJ//House3.obj", "OBJ//House3.mtl");
	//meshlist[MESH_HOUSE3]->textureArr[0] = LoadTGA("Image//House3.tga");

	meshlist[MESH_HOUSE4] = MeshBuilder::GenerateOBJMTL("House_4", "OBJ//House2.obj", "OBJ//House2.mtl");
	//meshlist[MESH_HOUSE4]->textureArr[0] = LoadTGA("Image//House2.tga");

	meshlist[MESH_HOUSE5] = MeshBuilder::GenerateOBJMTL("House_5", "OBJ//House1.obj", "OBJ//House1.mtl");
	//meshlist[MESH_HOUSE5]->textureArr[0] = LoadTGA("Image//House1.tga");

	meshlist[MESH_TOWER] = MeshBuilder::GenerateOBJMTL("Tower_1", "OBJ//Tower.obj", "OBJ//Tower.mtl"); 
	//meshlist[MESH_TOWER]->textureArr[0] = LoadTGA("Image//Tower.tga");

	//// <UI> 
	meshlist[MESH_STAMINABAR] = MeshBuilder::GenerateCube("Cube", Color(0.f, 1.f, 0.f), 1.f, 1.f, 1.f);

	meshlist[MESH_ICON] = MeshBuilder::GenerateQuad("Icon", Color(1.f, 0.f, 0.f), 1.0f);
	//// </UI> 

	//// <NPC> 
	meshlist[MESH_HEAD] = MeshBuilder::GenerateCube("Head", Color(1.f,1.f,0.f), 1.f, 1.f, 1.f);

	meshlist[MESH_AYAKA] = MeshBuilder::GenerateOBJMTL("Ayaka", "OBJ//Ayaka.obj", "OBJ//Ayaka.mtl");
	meshlist[MESH_AYAKA]->textureArr[0] = LoadTGA("Image//AyakaBody.tga");
	//meshlist[MESH_AYAKA]->textureArr[1] = LoadTGA("Image//AyakaHair.tga");
	//meshlist[MESH_AYAKA]->textureArr[2] = LoadTGA("Image//AyakeFace.tga");
	//// </NPC> 

	////Skybox
	meshlist[SKYBOX_FRONT] = MeshBuilder::GenerateQuad("Front of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_FRONT]->textureArr[0] = LoadTGA("Image//Skybox/miramar_ft.tga");

	meshlist[SKYBOX_BACK] = MeshBuilder::GenerateQuad("Back of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_BACK]->textureArr[0] = LoadTGA("Image//Skybox/miramar_bk.tga");

	meshlist[SKYBOX_TOP] = MeshBuilder::GenerateQuad("Top of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_TOP]->textureArr[0] = LoadTGA("Image//Skybox/miramar_up.tga");

	meshlist[SKYBOX_BOTTOM] = MeshBuilder::GenerateQuad("Bottom of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_BOTTOM]->textureArr[0] = LoadTGA("Image//Skybox/miramar_dn.tga");

	meshlist[SKYBOX_LEFT] = MeshBuilder::GenerateQuad("Left of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_LEFT]->textureArr[0] = LoadTGA("Image//Skybox/miramar_lf.tga");

	meshlist[SKYBOX_RIGHT] = MeshBuilder::GenerateQuad("Right of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_RIGHT]->textureArr[0] = LoadTGA("Image//Skybox/miramar_rt.tga");
}

MeshList::~MeshList()
{
}

Mesh* MeshList::GetMesh(MESH_TYPE meshtype)
{
	return meshlist[meshtype];
}

