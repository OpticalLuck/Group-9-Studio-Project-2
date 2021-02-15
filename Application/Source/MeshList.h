#pragma once
#include "Mesh.h"

class MeshList
{
public:
	enum MESH_TYPE
	{
		MESH_QUAD = 0,
		MESH_WALLS,
		MESH_LEVER,
		MESH_GARBAGE,
		MESH_LIGHT,
		MESH_TABLE,
		MESH_BENCH,
		MESH_BTNCASE,
		MESH_BTN,
		MESH_DOORFRAME,
		MESH_DOORLEFT,
		MESH_DOORRIGHT,
		MESH_AMRED,
		MESH_AMGREEN,
		MESH_AMGREENDEAD,
		MESH_KNIFE,
		TOTAL_MESH
	};

	MeshList();
	~MeshList();

	Mesh* GetMesh(MESH_TYPE meshtype);
private:
	Mesh* meshlist[TOTAL_MESH];
};

