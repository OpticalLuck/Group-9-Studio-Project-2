#include "Skybox.h"
Skybox::Skybox(GOManager gomanager, MeshList* meshlist, float Scale)
{			 
	Vector3 ScaleAll(Scale, Scale, Scale);
	SB_ARR[SBX_TOP] = gomanager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::SKYBOX_TOP));
	SB_ARR[SBX_TOP]->SetTranslate(Vector3(0, 50, 0) * Scale);
	SB_ARR[SBX_TOP]->SetRotate(Vector3(180, -90, 0));
	SB_ARR[SBX_TOP]->SetScale(ScaleAll);
			
	SB_ARR[SBX_BOTTOM] = gomanager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::SKYBOX_BOTTOM));
	SB_ARR[SBX_BOTTOM]->SetTranslate(Vector3(0, -50, 0) * Scale);
	SB_ARR[SBX_BOTTOM]->SetScale(ScaleAll);
	
	SB_ARR[SBX_LEFT] = gomanager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::SKYBOX_LEFT));
	SB_ARR[SBX_LEFT]->SetTranslate(Vector3(-50, 0, 0) * Scale);
	SB_ARR[SBX_LEFT]->SetRotate(Vector3(0, 90, -90));
	SB_ARR[SBX_LEFT]->SetScale(ScaleAll);

	SB_ARR[SBX_RIGHT] = gomanager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::SKYBOX_RIGHT));
	SB_ARR[SBX_RIGHT]->SetTranslate(Vector3(50, 0, 0) * Scale);
	SB_ARR[SBX_RIGHT]->SetRotate(Vector3(0, -90, 90));
	SB_ARR[SBX_RIGHT]->SetScale(ScaleAll);

	SB_ARR[SBX_BACK] = gomanager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::SKYBOX_BACK));
	SB_ARR[SBX_BACK]->SetTranslate(Vector3(0, 0, 50) * Scale);
	SB_ARR[SBX_BACK]->SetRotate(Vector3(-90, 0, 180));
	SB_ARR[SBX_BACK]->SetScale(ScaleAll);

	SB_ARR[SBX_FRONT] = gomanager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::SKYBOX_FRONT));
	SB_ARR[SBX_FRONT]->SetTranslate(Vector3(0, 0, -50) * Scale);
	SB_ARR[SBX_FRONT]->SetRotate(Vector3(90, 0, 0));
	SB_ARR[SBX_FRONT]->SetScale(ScaleAll);
}

Skybox::~Skybox()
{
}

GameObject* Skybox::GetSBX(int idx)
{
	return SB_ARR[idx];
}
