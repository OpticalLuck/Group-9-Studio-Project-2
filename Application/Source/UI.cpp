#include "UI.h"
#include "Application.h"

UI::UI():
	KeyPressed(false)
{

}

UI::~UI()
{

}

void UI::Init(Character* player)
{
	this->Player = player;
	staminaBar_width = 30;

	interactable = false;
	mapOpen = false;

	/*Quad = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));*/

	//Status: Walking
	text[0] = new Text();
	text[0]->SetMode(Text::STATIC_SCREENTEXT);
	text[0]->SetText("Walking");
	text[0]->SetTranslate(Vector3(0.f, 4, 0));

	//Status: Sprinting
	text[1] = new Text();
	text[1]->SetMode(Text::STATIC_SCREENTEXT);
	text[1]->SetText("Sprinting");
	text[1]->SetTranslate(Vector3(0.f, 4, 0));

	//Interactions
	text[2] = new Text();
	text[2]->SetMode(Text::STATIC_SCREENTEXT);
	text[2]->SetText("Press E to Interact");
	text[2]->SetTranslate(Vector3(50.5, 12.5, 0));

}

void UI::Update()
{
	staminaBar_width = Player->getStamina() / 2;

	if (Application::IsKeyPressed('M') && !KeyPressed)
	{
		mapOpen = !mapOpen;
		KeyPressed = true;
	}
	else if(!Application::IsKeyPressed('M') && KeyPressed)
	{
		KeyPressed = false;
	}

}

void UI::UpdateInteractions(GameObject* item)
{
	if (interactable == true)
	{
		if (item->getActive() == true)
		{
			text2active = true;
		}

		if (Application::IsKeyPressed('E'))
		{
			if (item->getActive())
			{
				item->SetActive(false);
				text2active = false;
			}
		}
	}
	else
	{
		text2active = false;
	}
}

void UI::Draw(Renderer* renderer, bool enableLight)
{
	if (mapOpen == false)
	{
		//render stamina bar if map is not open
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_STAMINABAR), 64, 10, staminaBar_width, 1);
	}
	else
	{
		//render map
		float x_offset = round(35 * (camera->GetPosX() / 30));
		float y_offset = round(35 * (camera->GetPosZ() / 30));
		
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_QUAD), 64, 36, 70, 70);
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_ICON), 64 + x_offset, 36 - y_offset, 1, 1);
	}

	if (camera->GetSprintState() == false && Player->getSprintState() == false)		//Walking
	{
		text[0]->Draw(renderer, enableLight);
	}
	else																			//Sprinting
	{
		text[1]->Draw(renderer, enableLight);
	}

	if (text2active == true)
	{
		text[2]->Draw(renderer, true);
	}
}

void UI::Exit()
{

}

GameObject* UI::getItem()
{
	return Item;
}

bool UI::getInteractable()
{
	return interactable;
}

void UI::setCamera(CameraVer2* camera)
{
	this->camera = camera;
}

void UI::setItem(GameObject* item)
{
	this->Item = item;
}

void UI::setInteractable(bool interactable)
{
	this->interactable = interactable;
}

