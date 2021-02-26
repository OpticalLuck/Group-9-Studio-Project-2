#pragma once
#include "MatrixStack.h"
#include "LoadCSV.h"
#include "Mesh.h"
#include "Light.h"

#include "Singleton.h"
struct TextData : public Singleton<TextData>
{
	int TextDataArr[256];
	TextData() { LoadTextData(TextDataArr, "Image//Gothic.csv"); std::cout << "TextArr Built" << std::endl; };
};

class Renderer
{
public:
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_MATERIAL_MAPKD,
		U_MATERIAL_MAPKD_ENABLED,
		U_LIGHTENABLED,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE_ENABLED2,
		U_COLOR_TEXTURE_ENABLED3,
		U_COLOR_TEXTURE_ENABLED4,
		U_COLOR_TEXTURE_ENABLED5,
		U_COLOR_TEXTURE_ENABLED6,
		U_COLOR_TEXTURE_ENABLED7,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,
		U_COLOR_TEXTURE2,
		U_COLOR_TEXTURE3,
		U_COLOR_TEXTURE4,
		U_COLOR_TEXTURE5,
		U_COLOR_TEXTURE6,
		U_COLOR_TEXTURE7,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL
	};
	Renderer(int numlight);
	~Renderer();

	void Reset();

	//Render
	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderDialogue(Mesh* mesh, std::string text, Color color, int index);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);

	//Transformation ModelStack
	void AddTransformation(Vector3 Translate, Vector3 Rotation = Vector3(0, 0, 0), Vector3 Scale = Vector3(1, 1, 1));
	void AddTranslate(float x, float y, float z);
	void AddRotate(float x, float y, float z);
	void AddScale(float x, float y, float z);

	//for character 
	void PushTransform();
	void PopTransform();
	void SetCamera(Vector3 position, Vector3 View, Vector3 Up);
	void SetToProj();
	void SetToOrtho();
	void SetLight(Light* light, Vector3 Camera_Offset);
	void LoadIdentity();
	unsigned GetprogramID();

	MS* GetMStack();
private:
	unsigned programID;
	unsigned Parameters[U_TOTAL];
	unsigned m_vertexArrayID;

	MS modelStack, viewStack, projectionStack;
};

