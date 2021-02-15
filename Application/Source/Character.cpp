#include "Character.h"


Character::Character(MeshList* meshlist):
	stabs(0),
	IsStabbed(false)
{
	CharacterArr[CHAR_AMRED] = new GameObject(Vector3(0, 2, 8), meshlist->GetMesh(meshlist->MESH_AMRED));
	CharacterArr[CHAR_AMRED]->SetScale(Vector3(0.2f, 0.2f, 0.2f));

	CharacterArr[CHAR_AMGREEN] = new GameObject(Vector3(8, 2, 0), meshlist->GetMesh(meshlist->MESH_AMGREEN));
	CharacterArr[CHAR_AMGREEN]->SetRotate(Vector3(0, -90, 0));
	CharacterArr[CHAR_AMGREEN]->SetScale(Vector3(0.2f, 0.2f, 0.2f));

	Accessories[ACC_KNIFE] = new GameObject(Vector3(-8, 2, 0), meshlist->GetMesh(meshlist->MESH_KNIFE));
	Accessories[ACC_KNIFE]->SetScale(Vector3(2,2,2));
	CharacterArr[CHAR_AMRED]->AddChild(Accessories[ACC_KNIFE]);
}

Character::~Character()
{
}

void Character::DrawAll(Renderer* renderer, bool EnableLight)
{
	for (int i = 0; i < CHAR_TOTAL; i++)
	{
		CharacterArr[i]->Draw(renderer, EnableLight);
	}
}

void Character::Kill(CameraVer2* camera, MeshList* meshlist, double dt)
{
	if (CharacterArr[CHAR_AMGREEN]->getInteracted() && !CharacterArr[CHAR_AMGREEN]->getIsDead())
	{
		GetAccessories(ACC_KNIFE)->SetPos(Vector3(-3, 2, 10));
		//Knife Rotation
		if (Accessories[ACC_KNIFE]->GetRotate().x < 90)
		{
			float rotatex = Accessories[ACC_KNIFE]->GetRotate().x;
			rotatex += 150 * dt;
			Accessories[ACC_KNIFE]->SetRotate(Vector3(rotatex, 0, 0));
		}
		else if (stabs < 3)
		{
			//Knife go in
			if (!IsStabbed)
			{
				if (Accessories[ACC_KNIFE]->GetTranslate().z < 6.f)
				{
					float translateZ = Accessories[ACC_KNIFE]->GetTranslate().z;
					translateZ += 50 * dt;
					Accessories[ACC_KNIFE]->SetTranslate(Vector3(0, 0, translateZ));
				}
				else
				{
					IsStabbed = true;
				}
			}
			//Knife go out
			else
			{
				if (Accessories[ACC_KNIFE]->GetTranslate().z > 0.f && IsStabbed)
				{
					float translateZ = Accessories[ACC_KNIFE]->GetTranslate().z;
					translateZ -= 50 * dt;
					Accessories[ACC_KNIFE]->SetTranslate(Vector3(0, 0, translateZ));

				}
				else
				{
					stabs++;
					IsStabbed = false;
				}
			}
			//Character now dead
		}
		else if (stabs == 3 && CharacterArr[CHAR_AMGREEN]->GetPRotate().x < 90)
		{
			float RotateX = CharacterArr[CHAR_AMGREEN]->GetPRotate().x;
			RotateX += 100 * dt;

			CharacterArr[CHAR_AMGREEN]->SetMesh(meshlist->GetMesh(meshlist->MESH_AMGREENDEAD));

			CharacterArr[CHAR_AMGREEN]->SetPRotate(Vector3(RotateX, 0, 0));
		}
		else
		{
			float Dist = (CharacterArr[CHAR_AMGREEN]->GetPos() - CharacterArr[CHAR_AMRED]->GetPos()).Length();
			camera->ToggleAnimation(Dist);
			camera->SetPosition(CharacterArr[CHAR_AMRED]->GetPos());
			CharacterArr[CHAR_AMGREEN]->SetInteracted(false);
			CharacterArr[CHAR_AMGREEN]->bTracking(false);
			CharacterArr[CHAR_AMGREEN]->SetIsDead(true);

			Accessories[ACC_KNIFE]->SetRotate(Vector3(0, 0, 0));
		}
	}
}




void Character::CamChange(CameraVer2 camera, Text* WorldText, Text* UI)
{
	if (camera.GetMode() == camera.FIRST_PERSON)
	{
		GetAccessories(ACC_KNIFE)->SetPos(Vector3(-3, 2, 10));

		if (CharacterArr[CHAR_AMRED]->inRange(CharacterArr[CHAR_AMGREEN], 5.f) && !CharacterArr[CHAR_AMGREEN]->getIsDead())
		{
			UI->SetActive(true);
			WorldText->SetActive(false);
		}
		else
		{
			UI->SetActive(false);
			WorldText->SetActive(false);
		}
	}
	else if (camera.GetMode() == camera.THIRD_PERSON)
	{
		GetAccessories(ACC_KNIFE)->SetPos(Vector3(-7, 2, 0));

		if (CharacterArr[CHAR_AMRED]->inRange(CharacterArr[CHAR_AMGREEN], 5.f) && !CharacterArr[CHAR_AMGREEN]->getIsDead())
		{
			UI->SetActive(false);
			WorldText->SetActive(true);
		}
		else
		{
			UI->SetActive(false);
			WorldText->SetActive(false);
		}
	}
}

GameObject* Character::GetCharacter(CHARACTER_TYPE type)
{
	return CharacterArr[type];
}

GameObject* Character::GetAccessories(ACCESSORY_TYPE type)
{
	return Accessories[type];
}

