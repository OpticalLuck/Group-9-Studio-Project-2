#pragma once
#include "Mesh.h"

class MeshList
{
public:
	enum MESH_TYPE
	{
		//PRIMATIVES
		MESH_AXIS = 0,
		MESH_QUAD,
		MESH_CUBE,

		//NPC

		//Environment
		MESH_FLOOR,
		
		MESH_HEAD,

		//UI
		MESH_STAMINABAR,
		MESH_ICON,

		//TOTAL NUMBER OF MESHES
		TOTAL_MESH
	};

	MeshList();
	~MeshList();

	Mesh* GetMesh(MESH_TYPE meshtype);
private:
	Mesh* meshlist[TOTAL_MESH];
};

