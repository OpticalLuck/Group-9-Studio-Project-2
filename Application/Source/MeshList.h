 #pragma once
#include "Mesh.h"
#include "TextureList.h"


class MeshList : public Singleton<MeshList>
{
public:
	enum MESH_TYPE
	{
		//PRIMATIVES
		MESH_AXIS = 0,
		MESH_QUAD,
		MESH_CUBE,

		//CHARACTER
		MESH_AYAKA,
		MESH_WING,

		//Environment
		MESH_LAND,
		MESH_FIELD,
		MESH_HOUSE1,
		MESH_HOUSE2,
		MESH_HOUSE3,
		MESH_TOWER,
		MESH_STADIUM,
		MESH_GATE,
		MESH_SCHOOL,
		MESH_LIBRARY,
		MESH_PAGODA,
		MESH_RING,
		MESH_FAN,

		//OBJECTS
		MESH_TABLE,
		MESH_PLANT,

		//NPC
		MESH_NPC,
		MESH_HEAD,

		//UI
		MESH_STAMINABAR,
		MESH_DIALOGUEBOX,
		MESH_ICON,

		//SKYBOX
		SKYBOX_TOP,
		SKYBOX_BOTTOM,
		SKYBOX_LEFT,
		SKYBOX_RIGHT,
		SKYBOX_FRONT,
		SKYBOX_BACK,

		//TOTAL NUMBER OF MESHES
		TOTAL_MESH
	};

	MeshList();
	~MeshList();

	Mesh* GetMesh(MESH_TYPE meshtype);
private:
	Mesh* meshlist[TOTAL_MESH];
};

