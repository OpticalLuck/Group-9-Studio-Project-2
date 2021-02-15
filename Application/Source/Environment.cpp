#include "Environment.h"
#include "MeshBuilder.h"
#include "MeshList.h"
Environment::Environment(MeshList* meshlist)
{
	for (int i = 0; i < TOTAL_OBJ; i++)
	{
		GOArr[i] = nullptr;
	}
	//ModelsEnvironment
	GOArr[OBJ_FLOOR] = new GameObject(Vector3(0,0,0), meshlist->GetMesh(meshlist->MESH_QUAD));
	GOArr[OBJ_FLOOR]->SetTexture("Image//Floor.tga");
	GOArr[OBJ_FLOOR]->SetScale(Vector3(62, 62, 62));

	GOArr[OBJ_WALLS] = new GameObject(Vector3(0, -0.5f, 0), meshlist->GetMesh(meshlist->MESH_WALLS));

	GOArr[OBJ_LIGHT1] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_LIGHT));
	GOArr[OBJ_LIGHT1]->SetScale(Vector3(0.2f, 0.2f, 0.2f));
	GOArr[OBJ_LIGHT1]->SetTexture("Image//Light.tga");

	GOArr[OBJ_LIGHT2] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_LIGHT));
	GOArr[OBJ_LIGHT2]->SetScale(Vector3(0.2f, 0.2f, 0.2f));
	GOArr[OBJ_LIGHT2]->SetTexture("Image//Light.tga");

	GOArr[OBJ_LIGHT3] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_LIGHT));
	GOArr[OBJ_LIGHT3]->SetScale(Vector3(0.2f, 0.2f, 0.2f));
	GOArr[OBJ_LIGHT3]->SetTexture("Image//Light.tga");

	GOArr[OBJ_LIGHT4] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_LIGHT));
	GOArr[OBJ_LIGHT4]->SetScale(Vector3(0.2f, 0.2f, 0.2f));
	GOArr[OBJ_LIGHT4]->SetTexture("Image//Light.tga");

	GOArr[OBJ_TABLE1] = new GameObject(Vector3(0, 2, 0), meshlist->GetMesh(meshlist->MESH_TABLE));
	GOArr[OBJ_TABLE2] = new GameObject(Vector3(15, 2, 15), meshlist->GetMesh(meshlist->MESH_TABLE));
	GOArr[OBJ_TABLE3] = new GameObject(Vector3(15, 2, -15), meshlist->GetMesh(meshlist->MESH_TABLE));
	GOArr[OBJ_TABLE4] = new GameObject(Vector3(-15, 2, 15), meshlist->GetMesh(meshlist->MESH_TABLE));
	GOArr[OBJ_TABLE5] = new GameObject(Vector3(-15, 2, -15), meshlist->GetMesh(meshlist->MESH_TABLE));

	GOArr[OBJ_DOORFRAME1] = new GameObject(Vector3(28.8f, 3.8f, -0.5f), meshlist->GetMesh(meshlist->MESH_DOORFRAME));
	GOArr[OBJ_DOORFRAME1]->SetTexture("Image//Door.tga");
	GOArr[OBJ_DOORFRAME1]->SetScale(Vector3(1.6f, 1.6f, 1.6f));

	GOArr[OBJ_DOORFRAME2] = new GameObject(Vector3(-29.5f, 3.8f, 0.5f), meshlist->GetMesh(meshlist->MESH_DOORFRAME));
	GOArr[OBJ_DOORFRAME2]->SetTexture("Image//Door.tga");
	GOArr[OBJ_DOORFRAME2]->SetRotate(Vector3(0, 180, 0));
	GOArr[OBJ_DOORFRAME2]->SetScale(Vector3(1.6f, 1.6f, 1.6f));

	GOArr[OBJ_DOORFRAME3] = new GameObject(Vector3(0.5f, 3.8f, 29.f), meshlist->GetMesh(meshlist->MESH_DOORFRAME));
	GOArr[OBJ_DOORFRAME3]->SetTexture("Image//Door.tga");
	GOArr[OBJ_DOORFRAME3]->SetRotate(Vector3(0, -90, 0));
	GOArr[OBJ_DOORFRAME3]->SetScale(Vector3(1.6f, 1.6f, 1.6f));

	GOArr[OBJ_BENCHUP] = new GameObject(Vector3(0, -1, -5), meshlist->GetMesh(meshlist->MESH_BENCH));
	GOArr[OBJ_BENCHUP]->SetRotate(Vector3(0, 90, 0));

	GOArr[OBJ_BENCHDOWN] = new GameObject(Vector3(0, -1, 5), meshlist->GetMesh(meshlist->MESH_BENCH));
	GOArr[OBJ_BENCHDOWN]->SetRotate(Vector3(0, 270, 0));

	GOArr[OBJ_BENCHLEFT] = new GameObject(Vector3(-5, -1, 0), meshlist->GetMesh(meshlist->MESH_BENCH));
	GOArr[OBJ_BENCHLEFT]->SetRotate(Vector3(0, 180, 0));

	GOArr[OBJ_BENCHRIGHT] = new GameObject(Vector3(5, -1, 0), meshlist->GetMesh(meshlist->MESH_BENCH));
	GOArr[OBJ_BENCHRIGHT]->SetRotate(Vector3(0, 0, 0));

	GOArr[OBJ_BTNCASE] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_BTNCASE));
	GOArr[OBJ_BTNCASE]->SetTexture("Image//ButtonCase.tga");
	GOArr[OBJ_BTN] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_BTN));
	GOArr[OBJ_DOOR1LEFT] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_DOORLEFT));
	GOArr[OBJ_DOOR1RIGHT] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_DOORRIGHT));
	GOArr[OBJ_DOOR2LEFT] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_DOORLEFT));
	GOArr[OBJ_DOOR2RIGHT] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_DOORRIGHT));
	GOArr[OBJ_DOOR3LEFT] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_DOORLEFT));
	GOArr[OBJ_DOOR3RIGHT] = new GameObject(Vector3(0, 0, 0), meshlist->GetMesh(meshlist->MESH_DOORRIGHT));
	
	GOArr[OBJ_LEVER] = new GameObject(Vector3(25, 4, -16.4f), meshlist->GetMesh(meshlist->MESH_LEVER));
	GOArr[OBJ_LEVER]->SetRotate(Vector3(0, -45, 0));

	GOArr[OBJ_GARBAGE] = new GameObject(Vector3(22.5f, 2.0f, -20), meshlist->GetMesh(meshlist->MESH_GARBAGE));
	//Table
	{
	GOArr[OBJ_TABLE1]->AddChild(GOArr[OBJ_BENCHUP]);
	GOArr[OBJ_TABLE1]->AddChild(GOArr[OBJ_BENCHDOWN]);
	GOArr[OBJ_TABLE1]->AddChild(GOArr[OBJ_BENCHLEFT]);
	GOArr[OBJ_TABLE1]->AddChild(GOArr[OBJ_BENCHRIGHT]);
	GOArr[OBJ_TABLE1]->AddChild(GOArr[OBJ_BTNCASE]);
	GOArr[OBJ_TABLE1]->AddChild(GOArr[OBJ_BTN]);

	
	GOArr[OBJ_TABLE2]->AddChild(GOArr[OBJ_BENCHUP]);
	GOArr[OBJ_TABLE2]->AddChild(GOArr[OBJ_BENCHDOWN]);
	GOArr[OBJ_TABLE2]->AddChild(GOArr[OBJ_BENCHLEFT]);
	GOArr[OBJ_TABLE2]->AddChild(GOArr[OBJ_BENCHRIGHT]);

	GOArr[OBJ_TABLE3]->AddChild(GOArr[OBJ_BENCHUP]);
	GOArr[OBJ_TABLE3]->AddChild(GOArr[OBJ_BENCHDOWN]);
	GOArr[OBJ_TABLE3]->AddChild(GOArr[OBJ_BENCHLEFT]);
	GOArr[OBJ_TABLE3]->AddChild(GOArr[OBJ_BENCHRIGHT]);

	GOArr[OBJ_TABLE4]->AddChild(GOArr[OBJ_BENCHUP]);
	GOArr[OBJ_TABLE4]->AddChild(GOArr[OBJ_BENCHDOWN]);
	GOArr[OBJ_TABLE4]->AddChild(GOArr[OBJ_BENCHLEFT]);
	GOArr[OBJ_TABLE4]->AddChild(GOArr[OBJ_BENCHRIGHT]);

	GOArr[OBJ_TABLE5]->AddChild(GOArr[OBJ_BENCHUP]);
	GOArr[OBJ_TABLE5]->AddChild(GOArr[OBJ_BENCHDOWN]);
	GOArr[OBJ_TABLE5]->AddChild(GOArr[OBJ_BENCHLEFT]);
	GOArr[OBJ_TABLE5]->AddChild(GOArr[OBJ_BENCHRIGHT]);
	}

	//Door
	{
		GOArr[OBJ_DOORFRAME1]->AddChild(GOArr[OBJ_DOOR1LEFT]);
		GOArr[OBJ_DOORFRAME1]->AddChild(GOArr[OBJ_DOOR1RIGHT]);
		GOArr[OBJ_DOORFRAME2]->AddChild(GOArr[OBJ_DOOR2LEFT]);
		GOArr[OBJ_DOORFRAME2]->AddChild(GOArr[OBJ_DOOR2RIGHT]);
		GOArr[OBJ_DOORFRAME3]->AddChild(GOArr[OBJ_DOOR3LEFT]);
		GOArr[OBJ_DOORFRAME3]->AddChild(GOArr[OBJ_DOOR3RIGHT]);
	}
}

Environment::~Environment()
{
}

void Environment::Draw(Renderer* renderer)
{
	for (int i = 0; i < TOTAL_OBJ; i++)
	{
		if (GOArr[i])
		{
			if (i == OBJ_LIGHT1 || i == OBJ_LIGHT2 || i == OBJ_LIGHT3 || i == OBJ_LIGHT4)
			{
				GOArr[i]->Draw(renderer, false);
			}
			else if (i > OBJ_BENCHUP && i < TOTAL_OBJ)
			{
				//
			}
			else
			{
				GOArr[i]->Draw(renderer, true);
			}
		}
	}
}

void Environment::SetCoord(OBJ_TYPE obj, Vector3 Coord)
{
	GOArr[obj]->SetPos(Coord);
}

void Environment::DoorInteract(OBJ_TYPE obj, bool inRange, float dt)
{
	if (inRange)
	{
		if (GOArr[obj]->GetChild(0)->GetTranslate().z < 2.f) //Door Open
		{
			float translate = GOArr[obj]->GetChild(0)->GetTranslate().z + 5 * dt;
			GOArr[obj]->GetChild(0)->SetTranslate(Vector3(0, 0, translate));
			GOArr[obj]->GetChild(1)->SetTranslate(Vector3(0, 0, -translate));
		}
	}
	else
	{
		if (GOArr[obj]->GetChild(0)->GetTranslate().z > 0.f) //Door Close
		{
			float translate = GOArr[obj]->GetChild(0)->GetTranslate().z - 5 * dt;
			GOArr[obj]->GetChild(0)->SetTranslate(Vector3(0, 0, translate));
			GOArr[obj]->GetChild(1)->SetTranslate(Vector3(0, 0, -translate));
		}
		else
		{
			GOArr[obj]->GetChild(0)->SetTranslate(Vector3(0, 0, 0));
			GOArr[obj]->GetChild(1)->SetTranslate(Vector3(0, 0, 0));
		}
	}
}

void Environment::BtnInteract(GameObject* GO, double dt)
{
	if (GOArr[OBJ_BTN]->getInteracted())
	{
		if (GOArr[OBJ_BTN]->GetPos().y > -0.4f)
		{
			float y_change = GOArr[OBJ_BTN]->GetTranslate().y - dt;

			GOArr[OBJ_BTN]->SetTranslate(Vector3(0, y_change, 0));
		}
		else
		{
			GO->SetInteracted(true);
			GOArr[OBJ_BTN]->SetInteracted(false);
		}
	}
	else if  (GOArr[OBJ_BTN]->GetPos().y < 0.f)
	{
		float y_change = GOArr[OBJ_BTN]->GetTranslate().y + dt;
		GOArr[OBJ_BTN]->SetTranslate(Vector3(0, y_change, 0));
	}
}

GameObject* Environment::GetArr(OBJ_TYPE obj)
{
	return GOArr[obj];
}
