#pragma once
#include "Mesh.h"

class MeshList
{
public:
	enum MESH_TYPE
	{
		MESH_AXIS = 0,
		MESH_QUAD,
		TOTAL_MESH
	};

	MeshList();
	~MeshList();

	Mesh* GetMesh(MESH_TYPE meshtype);
private:
	Mesh* meshlist[TOTAL_MESH];
};

