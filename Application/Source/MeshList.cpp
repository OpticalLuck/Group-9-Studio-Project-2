#include "MeshList.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
MeshList::MeshList(TextureList* texturelist)
{
	//// <PRIMATIVES> 
	meshlist[MESH_AXIS] = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);
	meshlist[MESH_QUAD] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));
	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	//// </PRIMATIVES> 
	
	//0 is diffuse
	//1 is specular

	meshlist[MESH_FLOOR] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));
	meshlist[MESH_FLOOR]->textureArr[0] = texturelist->Insert("Floor.tga");

	meshlist[MESH_HOUSE1] = MeshBuilder::GenerateOBJMTL("House_1", "OBJ//JP_HOUSE_1.obj", "OBJ//JP_HOUSE_1.mtl");
	meshlist[MESH_HOUSE1]->textureArr[0] = texturelist->Insert("JP_HOUSE_1_DIFFUSE.tga");
	meshlist[MESH_HOUSE1]->textureArr[1] = texturelist->Insert("JP_HOUSE_1_SPECULAR.tga");

	meshlist[MESH_HOUSE2] = MeshBuilder::GenerateOBJMTL("House_2", "OBJ//JP_HOUSE_2.obj", "OBJ//JP_HOUSE_2.mtl");
	meshlist[MESH_HOUSE2]->textureArr[0] = texturelist->Insert("JP_HOUSE_2_DIFFUSE.tga");
	meshlist[MESH_HOUSE2]->textureArr[1] = texturelist->Insert("JP_HOUSE_2_SPECULAR.tga");

	meshlist[MESH_HOUSE3] = MeshBuilder::GenerateOBJMTL("House_3", "OBJ//JP_HOUSE_3.obj", "OBJ//JP_HOUSE_3.mtl");
	meshlist[MESH_HOUSE3]->textureArr[0] = texturelist->Insert("JP_HOUSE_3_DIFFUSE.tga");
	meshlist[MESH_HOUSE3]->textureArr[1] = texturelist->Insert("JP_HOUSE_3_SPECULAR.tga");
	
	//meshlist[MESH_HOUSE5] = MeshBuilder::GenerateOBJMTL("House_5", "OBJ//House1.obj", "OBJ//House1.mtl");
	//meshlist[MESH_HOUSE5]->textureArr[0] = texturelist->Insert("House1.tga");

	//meshlist[MESH_TOWER] = MeshBuilder::GenerateOBJMTL("Tower_1", "OBJ//Tower.obj", "OBJ//Tower.mtl"); 
	//meshlist[MESH_TOWER]->textureArr[0] = texturelist->Insert("Tower.tga");

	//// <UI> 
	meshlist[MESH_STAMINABAR] = MeshBuilder::GenerateCube("Cube", Color(0.f, 1.f, 0.f), 1.f, 1.f, 1.f);

	meshlist[MESH_ICON] = MeshBuilder::GenerateQuad("Icon", Color(1.f, 0.f, 0.f), 1.0f);
	//// </UI> 

	//// <NPC> 
	meshlist[MESH_HEAD] = MeshBuilder::GenerateCube("Head", Color(1.f,1.f,0.f), 1.f, 1.f, 1.f);
	meshlist[MESH_AYAKA] = MeshBuilder::GenerateOBJMTL("Ayaka", "OBJ//Ayaka.obj", "OBJ//Ayaka.mtl", texturelist);
	//// </NPC> 

	////Skybox
	meshlist[SKYBOX_FRONT] = MeshBuilder::GenerateQuad("Front of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_FRONT]->textureArr[0] = texturelist->Insert("Skybox/miramar_ft.tga");

	meshlist[SKYBOX_BACK] = MeshBuilder::GenerateQuad("Back of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_BACK]->textureArr[0] = texturelist->Insert("Skybox/miramar_bk.tga");

	meshlist[SKYBOX_TOP] = MeshBuilder::GenerateQuad("Top of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_TOP]->textureArr[0] = texturelist->Insert("Skybox/miramar_up.tga");

	meshlist[SKYBOX_BOTTOM] = MeshBuilder::GenerateQuad("Bottom of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_BOTTOM]->textureArr[0] = texturelist->Insert("Skybox/miramar_dn.tga");

	meshlist[SKYBOX_LEFT] = MeshBuilder::GenerateQuad("Left of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_LEFT]->textureArr[0] = texturelist->Insert("Skybox/miramar_lf.tga");

	meshlist[SKYBOX_RIGHT] = MeshBuilder::GenerateQuad("Right of Skybox", Color(1, 1, 1), 100.2f);
	meshlist[SKYBOX_RIGHT]->textureArr[0] = texturelist->Insert("Skybox/miramar_rt.tga");
}

MeshList::~MeshList()
{
}

Mesh* MeshList::GetMesh(MESH_TYPE meshtype)
{
	return meshlist[meshtype];
}

