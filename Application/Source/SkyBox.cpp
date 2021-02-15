#include "SkyBox.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include <sstream>

SkyBox::SkyBox()
{
	std::stringstream ss;
	Vector3 position;
	for (int i = 0; i < F_TOTAL; i++)
	{
		faces[i] = new GameObject();
		faces[i]->SetMesh(MeshBuilder::GenerateQuad("SkyBoxQuads", Color(1, 1, 1)));
		faces[i]->SetScale(Vector3(1000, 1000, 1000));
		ss.str("");
		ss << "Image//";
		switch (i)
		{
		case F_FRONT:
			position = Vector3(0, 0, -499);
			faces[i]->SetRotate(Vector3(90, 0, 0));
			ss << "front.tga";
			break;
		case F_BACK:
			position = Vector3(0, 0, 499);
			faces[i]->SetRotate(Vector3(90, 0, 180));
			ss << "back.tga";
			break;
		case F_TOP:
			position = Vector3(0, 498, 0);
			faces[i]->SetRotate(Vector3(180, 0, 0));
			ss << "top.tga";
			break;
		case F_BOTTOM:
			position = Vector3(0, -499, 0);
			ss << "bottom.tga";
			break;
		case F_LEFT:
			position = Vector3(-499, 0, 0);
			faces[i]->SetRotate(Vector3(90, 0, -90));
			ss << "left.tga";
			break;
		case F_RIGHT:
			position = Vector3(499, 0, 0);
			faces[i]->SetRotate(Vector3(90, 0, 90));
			ss << "right.tga";
		}
		faces[i]->SetPos(position);
		faces[i]->GetMesh()->textureID = LoadTGA(ss.str().c_str());
	}
}

SkyBox::~SkyBox()
{
}

void SkyBox::Draw(Renderer* renderer)
{
	for (int i = 0; i < F_TOTAL; i++)
	{
		renderer->PushTransform();
		renderer->AddTransformation(faces[i]->GetTranslate(), faces[i]->GetPos(), faces[i]->GetRotate() , faces[i]->GetScale());
		renderer->RenderMesh(faces[i]->GetMesh(), false);
		renderer->PopTransform();
	}
}
