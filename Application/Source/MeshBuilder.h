#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "TextureList.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float width = 1.0f, float height = 1.0f);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateWireCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCircle(const std::string& meshName, std::string axis, float radius);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateHemisphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius, bool hollow);
	static Mesh* GenerateCylinder(const std::string& meshName, Color color, float numStack, float height, float radius, bool hollow);
	static Mesh* GenConeFrust(const std::string& meshName, Color color, float numStack, float height, float topradius, Position topoffset, float btmradius, bool hollow);
	
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path);
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol, int TextDataArr[]);
	static Mesh* GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path, TextureList* texturelist = nullptr);

};

#endif