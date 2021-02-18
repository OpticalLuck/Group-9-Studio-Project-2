#pragma once
#include "Mesh.h"

class MeshList
{
public:
	enum MESH_TYPE
	{
		MESH_AXIS = 0,
		MESH_QUAD,

		//Environment
		MESH_FLOOR,
		
		MESH_HEAD,
		MESH_CUBE,
		MESH_STAMINABAR,
		MESH_ICON,
		TOTAL_MESH
	};

	MeshList();
	~MeshList();

	Mesh* GetMesh(MESH_TYPE meshtype);
private:
	Mesh* meshlist[TOTAL_MESH];
};

