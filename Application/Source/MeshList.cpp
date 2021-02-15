#include "MeshList.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
MeshList::MeshList()
{
	meshlist[MESH_QUAD] = MeshBuilder::GenerateQuad("FloorQuad", Color(1,1,1));
	
	meshlist[MESH_WALLS] = MeshBuilder::GenerateOBJMTL("WALLS", "OBJ//Walls2.obj", "OBJ//Walls2.mtl");
	
	meshlist[MESH_LIGHT] = MeshBuilder::GenerateOBJMTL("LIGHT", "OBJ//Light.obj", "OBJ//Light.mtl");
	meshlist[MESH_LIGHT]->textureID = LoadTGA("Image//Light.tga");
	
	meshlist[MESH_TABLE] = MeshBuilder::GenerateOBJMTL("TABLE", "OBJ//Table.obj", "OBJ//Table.mtl");

	meshlist[MESH_LEVER] = MeshBuilder::GenerateOBJMTL("LEVER", "OBJ//Lever.obj", "OBJ//Lever.mtl");

	meshlist[MESH_GARBAGE] = MeshBuilder::GenerateOBJMTL("GARBAGE", "OBJ//Garbage.obj", "OBJ//Garbage.mtl");
	
	meshlist[MESH_BENCH] = MeshBuilder::GenerateOBJMTL("BENCH", "OBJ//Bench.obj", "OBJ//Bench.mtl");
	
	meshlist[MESH_BTNCASE] = MeshBuilder::GenerateOBJMTL("BTNCASE", "OBJ//ButtonCase.obj", "OBJ//ButtonCase.mtl");
	
	meshlist[MESH_BTN] = MeshBuilder::GenerateOBJMTL("BUTTON", "OBJ//Button.obj", "OBJ//Button.mtl");
	
	meshlist[MESH_DOORFRAME] = MeshBuilder::GenerateOBJMTL("ButtonFrame", "OBJ//DoorFrame.obj", "OBJ//DoorFrame.mtl");
	meshlist[MESH_DOORFRAME]->textureID = LoadTGA("Image//Door.tga");
	
	meshlist[MESH_DOORLEFT] = MeshBuilder::GenerateOBJMTL("DOORLEFT", "OBJ//DoorLeft.obj", "OBJ//DoorLeft.mtl");
	meshlist[MESH_DOORLEFT]->textureID = LoadTGA("Image//Door.tga");
	
	meshlist[MESH_DOORRIGHT] = MeshBuilder::GenerateOBJMTL("DOORRIGHT", "OBJ//DoorRight.obj", "OBJ//DoorRight.mtl");
	meshlist[MESH_DOORRIGHT]->textureID = LoadTGA("Image//Door.tga");	

	meshlist[MESH_AMRED] = MeshBuilder::GenerateOBJMTL("AMONGUS", "OBJ//Character1.obj", "OBJ//Character1.mtl");
	meshlist[MESH_AMRED]->textureID = LoadTGA("Image//RedAM.tga");

	meshlist[MESH_AMGREEN] = MeshBuilder::GenerateOBJMTL("AMONGUS", "OBJ//Character1.obj", "OBJ//Character1.mtl");
	meshlist[MESH_AMGREEN]->textureID = LoadTGA("Image//GreenAM.tga");

	meshlist[MESH_AMGREENDEAD] = MeshBuilder::GenerateOBJMTL("AMONGUS", "OBJ//AMDead.obj", "OBJ//AMDead.mtl");
	meshlist[MESH_AMGREENDEAD]->textureID = LoadTGA("Image//GreenAMDEAD.tga");

	meshlist[MESH_KNIFE] = MeshBuilder::GenerateOBJMTL("KNIFE", "OBJ//Knife.obj", "OBJ//Knife.mtl");
	meshlist[MESH_KNIFE]->textureID = LoadTGA("Image//KnifeColor.tga");
}

MeshList::~MeshList()
{
}

Mesh* MeshList::GetMesh(MESH_TYPE meshtype)
{
	return meshlist[meshtype];
}

