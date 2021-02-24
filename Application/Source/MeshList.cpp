#include "MeshList.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
MeshList::MeshList()
{
	TextureList* texturelist = TextureList::GetInstance();
	std::cout << "Mesh Loaded" << std::endl;

	//// <PRIMATIVES> 
	meshlist[MESH_AXIS] = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);
	meshlist[MESH_QUAD] = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1));
	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	//// </PRIMATIVES> 
	
	//0 is diffuse
	//1 is specular
	//2 is roughness tbc

	meshlist[MESH_FLOOR] = MeshBuilder::GenerateQuad("FloorQuad", Color(1, 1, 1));
	meshlist[MESH_FLOOR]->textureArr[0] = texturelist->Insert("Floor.tga");

	meshlist[MESH_HOUSE1] = MeshBuilder::GenerateOBJMTL("House_1", "OBJ//House/JP_HOUSE_1.obj", "OBJ///House/JP_HOUSE_1.mtl");
	meshlist[MESH_HOUSE1]->textureArr[0] = texturelist->Insert("House/JP_HOUSE_1_DIFFUSE.tga");
	meshlist[MESH_HOUSE1]->textureArr[1] = texturelist->Insert("House/JP_HOUSE_1_SPECULAR.tga");

	meshlist[MESH_HOUSE2] = MeshBuilder::GenerateOBJMTL("House_2", "OBJ//House/JP_HOUSE_2.obj", "OBJ///House/JP_HOUSE_2.mtl");
	meshlist[MESH_HOUSE2]->textureArr[0] = texturelist->Insert("House/JP_HOUSE_2_DIFFUSE.tga");
	meshlist[MESH_HOUSE2]->textureArr[1] = texturelist->Insert("House/JP_HOUSE_2_SPECULAR.tga");

	meshlist[MESH_HOUSE3] = MeshBuilder::GenerateOBJMTL("House_3", "OBJ///House/JP_HOUSE_3.obj", "OBJ///House/JP_HOUSE_3.mtl");
	meshlist[MESH_HOUSE3]->textureArr[0] = texturelist->Insert("House/JP_HOUSE_3_DIFFUSE.tga");
	meshlist[MESH_HOUSE3]->textureArr[1] = texturelist->Insert("House/JP_HOUSE_3_SPECULAR.tga");

	meshlist[MESH_STADIUM] = MeshBuilder::GenerateOBJMTL("Field", "OBJ//Stadium/Stadium.obj", "OBJ//Stadium/Stadium.mtl");
	meshlist[MESH_STADIUM]->textureArr[0] = texturelist->Insert("Stadium/Stadium.tga");

	meshlist[MESH_GATE] = MeshBuilder::GenerateOBJMTL("Torii", "OBJ//Gate/Gate.obj", "OBJ//Gate/Gate.mtl");
	meshlist[MESH_GATE]->textureArr[0] = texturelist->Insert("Gate/Gate_Diffuse.tga");

	meshlist[MESH_SCHOOL] = MeshBuilder::GenerateOBJMTL("School", "OBJ//School/School.obj", "OBJ//School/School.mtl");
	meshlist[MESH_SCHOOL]->textureArr[0] = texturelist->Insert("School/School.tga");

	meshlist[MESH_LIBRARY] = MeshBuilder::GenerateOBJMTL("Library", "OBJ//Library/Library.obj", "OBJ//Library/Library.mtl");
	meshlist[MESH_LIBRARY]->textureArr[0] = texturelist->Insert("Library/Library_Diffuse.tga");

	meshlist[MESH_PAGODA] = MeshBuilder::GenerateOBJMTL("Pagoda", "OBJ//Pagoda/Pagoda.obj", "OBJ//Pagoda/Pagoda.mtl");
	meshlist[MESH_PAGODA]->textureArr[0] = texturelist->Insert("Pagoda/Pagoda.tga");

	meshlist[MESH_TABLE] = MeshBuilder::GenerateOBJMTL("Table", "OBJ//Hall/table.obj", "OBJ//Hall/table.mtl");
	meshlist[MESH_TABLE]->textureArr[0] = texturelist->Insert("table.tga");
	
	meshlist[MESH_PLANT] = MeshBuilder::GenerateOBJMTL("Table", "OBJ//Hall/plant.obj", "OBJ//Hall/plant.mtl");
	meshlist[MESH_PLANT]->textureArr[0] = texturelist->Insert("plant.tga");

	meshlist[MESH_RING] = MeshBuilder::GenerateOBJMTL("Pagoda", "OBJ//Ring/Ring.obj", "OBJ//Ring/Ring.mtl");

	//// <UI> 
	meshlist[MESH_STAMINABAR] = MeshBuilder::GenerateCube("Cube", Color(0.f, 1.f, 0.f), 1.f, 1.f, 1.f);
	meshlist[MESH_DIALOGUEBOX] = MeshBuilder::GenerateCube("For the Dialogue", Color(0.502f, 0.502f, 0.502f), 1.f, 1.f, 1.f);

	meshlist[MESH_ICON] = MeshBuilder::GenerateQuad("Icon", Color(1.f, 0.f, 0.f), 1.0f);
	//// </UI> 

	//// <NPC> 
	meshlist[MESH_HEAD] = MeshBuilder::GenerateCube("Head", Color(1.f,1.f,0.f), 1.f, 1.f, 1.f);
	meshlist[MESH_AYAKA] = MeshBuilder::GenerateOBJMTL("Ayaka", "OBJ//Ayaka.obj", "OBJ//Ayaka.mtl", texturelist);

	meshlist[MESH_WING] = MeshBuilder::GenerateOBJMTL("Ayaka", "OBJ//Wing/Wing.obj", "OBJ//Wing/Wing.mtl");
	meshlist[MESH_WING]->textureArr[0] = texturelist->Insert("Wing/Wing.tga");
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

