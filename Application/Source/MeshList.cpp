#include "MeshList.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Renderer.h"
MeshList::MeshList()
{
	TextureList* texturelist = TextureList::GetInstance();

	//// <PRIMATIVES> 
	meshlist[MESH_AXIS] = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);
	meshlist[MESH_QUAD] = MeshBuilder::GenerateQuad("Quad", Color(0.5f, 0.5f, 0.5f));
	meshlist[MESH_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	meshlist[MESH_CUBE2] = MeshBuilder::GenerateCube("Cube", Color(0.545f, 0.271f, 0.075f), 1.f, 1.f, 1.f);
	//// </PRIMATIVES> 
	
	//0 is diffuse
	//1 is specular
	//2 is roughness tbc

	meshlist[MESH_LAND] = MeshBuilder::GenerateQuad("CityLand", Color(1, 1, 1));
	meshlist[MESH_LAND]->textureArr[0] = texturelist->Insert("GrassLand.tga");

	meshlist[MESH_FIELD] = MeshBuilder::GenerateQuad("StadiumField", Color(1, 1, 1));
	meshlist[MESH_FIELD]->textureArr[0] = texturelist->Insert("Field.tga");
	
	meshlist[MESH_GRASS] = MeshBuilder::GenerateQuad("GrassFloor", Color(1, 1, 1));
	meshlist[MESH_GRASS]->textureArr[0] = texturelist->Insert("Lush.tga");
	//// <MAIN CHARACTER>
	meshlist[MESH_AYAKA] = MeshBuilder::GenerateOBJMTL("Ayaka", "OBJ//Ayaka.obj", "OBJ//Ayaka.mtl", texturelist);
	meshlist[MESH_WING] = MeshBuilder::GenerateOBJMTL("Ayaka", "OBJ//Wing/Wing.obj", "OBJ//Wing/Wing.mtl");
	meshlist[MESH_WING]->textureArr[0] = texturelist->Insert("Wing/Wing.tga");
	//// <\MAIN CHARACTER>

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
	
	meshlist[MESH_PLANT] = MeshBuilder::GenerateOBJMTL("Plant", "OBJ//Hall/plant.obj", "OBJ//Hall/plant.mtl");
	meshlist[MESH_PLANT]->textureArr[0] = texturelist->Insert("plant.tga");

	meshlist[MESH_RING] = MeshBuilder::GenerateOBJMTL("Ring", "OBJ//Ring/Ring.obj", "OBJ//Ring/Ring.mtl");

	meshlist[MESH_FAN] = MeshBuilder::GenerateOBJMTL("Fan", "OBJ//Fan.obj", "OBJ//Fan.mtl");

	meshlist[MESH_TREE] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//Trees/tree_pineDefaultA.obj", "OBJ//Trees/tree_pineDefaultA.mtl");
	
	meshlist[MESH_INDOORWALL] = MeshBuilder::GenerateQuad("Wall", Color(0.5f, 0.5f, 0.5f));
	meshlist[MESH_INDOORWALL]->textureArr[0] = texturelist->Insert("jp.tga");

	meshlist[MESH_PLATFORM] = MeshBuilder::GenerateCube("Platform", Color(1.0f, 1.f, 1.0f), 1 , 1, 1);
	meshlist[MESH_PLATFORM]->textureArr[0] = texturelist->Insert("table.tga");

	meshlist[MESH_TRAIN] = MeshBuilder::GenerateOBJMTL("train", "OBJ//Train/amazingtram.obj", "OBJ//Train/amazingtram.mtl");
	meshlist[MESH_TRAINDOOR] = MeshBuilder::GenerateOBJMTL("train", "OBJ//Train/door.obj", "OBJ//Train/door.mtl");

	meshlist[MESH_PORTAL] = MeshBuilder::GenerateQuad("Portal", Color(0, 0.8, 0.8), 1, 2);

	meshlist[MESH_GEM] = MeshBuilder::GenerateOBJMTL("Gem", "OBJ//jewel.obj", "OBJ//jewel.mtl");

	meshlist[MESH_KEY] = MeshBuilder::GenerateOBJMTL("Key", "OBJ//key.obj", "OBJ//key.mtl");

	//// <UI> 
	meshlist[MESH_TEXT] = MeshBuilder::GenerateText("Text", 16, 16, TextData::GetInstance()->TextDataArr);
	meshlist[MESH_TEXT]->textureArr[0] = texturelist->Insert("Gothic.tga");

	meshlist[MESH_STAMINABAR] = MeshBuilder::GenerateCube("Cube", Color(0.f, 1.f, 0.f), 1.f, 1.f, 1.f);
	meshlist[MESH_DIALOGUEBOX] = MeshBuilder::GenerateCube("For the Dialogue", Color(0.502f, 0.502f, 0.502f), 1.f, 1.f, 1.f);

	meshlist[MESH_PAUSEBG] = MeshBuilder::GenerateQuad("PauseBG", Color(1.f, 1.f, 1.f), 75, 75);
	meshlist[MESH_PAUSEBG]->textureArr[0] = texturelist->Insert("PauseMenu.tga");

	meshlist[MESH_CONTROLS] = MeshBuilder::GenerateQuad("Quad", Color(0.5f, 0.5f, 0.5f), 128, 72);
	meshlist[MESH_CONTROLS]->textureArr[0] = texturelist->Insert("Controls.tga");


	//// </UI> 

	//// <NPC> 
	meshlist[MESH_NPC] = MeshBuilder::GenerateOBJMTL("Body", "OBJ//NPC/npcbody.obj", "OBJ//NPC/npcbody.mtl");
	meshlist[MESH_HEAD] = MeshBuilder::GenerateOBJMTL("Head", "OBJ//NPC/fixedhead.obj", "OBJ//NPC/fixedhead.mtl");
	meshlist[MESH_HEAD]->textureArr[0] = texturelist->Insert("NPC/stoopfacenumber2.tga");
	//// </NPC> 

	////Skybox
	meshlist[SKYBOX_FRONT] = MeshBuilder::GenerateQuad("Front of Skybox", Color(1, 1, 1), 100.2f, 100.2f);
	meshlist[SKYBOX_FRONT]->textureArr[0] = texturelist->Insert("Skybox/miramar_ft.tga");

	meshlist[SKYBOX_BACK] = MeshBuilder::GenerateQuad("Back of Skybox", Color(1, 1, 1), 100.2f, 100.2f);
	meshlist[SKYBOX_BACK]->textureArr[0] = texturelist->Insert("Skybox/miramar_bk.tga");

	meshlist[SKYBOX_TOP] = MeshBuilder::GenerateQuad("Top of Skybox", Color(1, 1, 1), 100.2f, 100.2f);
	meshlist[SKYBOX_TOP]->textureArr[0] = texturelist->Insert("Skybox/miramar_up.tga");

	meshlist[SKYBOX_BOTTOM] = MeshBuilder::GenerateQuad("Bottom of Skybox", Color(1, 1, 1), 100.2f, 100.2f);
	meshlist[SKYBOX_BOTTOM]->textureArr[0] = texturelist->Insert("Skybox/miramar_dn.tga");

	meshlist[SKYBOX_LEFT] = MeshBuilder::GenerateQuad("Left of Skybox", Color(1, 1, 1), 100.2f, 100.2f);
	meshlist[SKYBOX_LEFT]->textureArr[0] = texturelist->Insert("Skybox/miramar_lf.tga");

	meshlist[SKYBOX_RIGHT] = MeshBuilder::GenerateQuad("Right of Skybox", Color(1, 1, 1), 100.2f, 100.2f);
	meshlist[SKYBOX_RIGHT]->textureArr[0] = texturelist->Insert("Skybox/miramar_rt.tga");
}

MeshList::~MeshList()
{
	for (int i = 0; i < TOTAL_MESH; i++)
	{
		delete meshlist[i];
	}
}

Mesh* MeshList::GetMesh(MESH_TYPE meshtype)
{
	return meshlist[meshtype];
}

