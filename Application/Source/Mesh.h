#ifndef MESH_H
#define MESH_H
#define MAX_TEXTURES 8

#include <string>
#include <vector>
#include "Material.h"

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum class DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_TRIANGLE_FAN,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();
	void Render(unsigned offset, unsigned count);

	Material material;	
	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	//unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	//unsigned textureID;
	unsigned textureArr[MAX_TEXTURES];
	std::vector<Material> materials;
	static unsigned locationKa;
	static unsigned locationKd;
	static unsigned locationKs;
	static unsigned locationNs;
	static unsigned locationMap_Kd;

	static void SetMaterialLoc(unsigned kA, unsigned kD, unsigned kS, unsigned nS, unsigned map_Kd);
};

#endif