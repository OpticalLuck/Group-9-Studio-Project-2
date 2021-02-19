#include "UI.h"
#include "Application.h"

UI::UI()
{

}

UI::~UI()
{

}

void UI::Init(GameObject* player)
{
	this->Player = player;
	staminaBar_width = 30;

	tempMeshList = new MeshList();

	interactable = false;

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
	text[2]->SetTranslate(Vector3(27.5, 12.5, 0));

}

void UI::Update()
{
	camera->SetSprintState(false);
	if (Application::IsKeyPressed(VK_SHIFT) && (Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D')))
	{
		//Using Stamina Bar
		if (staminaBar_width >= 0)
		{
			camera->SetSprintState(true);
			staminaBar_width -= 0.3;
		}
	}
	else
	{
		//Recharging Stamina Bar
		if (staminaBar_width <= 30)
		{
			staminaBar_width += 0.3;
		}
	}
}

void UI::UpdateInteractions()
{
	if (interactable == true)
	{
		//std::cout << "in range of item" << std::endl;

		if (Item->getActive() == true)
		{
			text2active = true;
		}

		if (Application::IsKeyPressed('E'))
		{
			if (getItem()->getActive())
			{
				getItem()->SetActive(false);
				text2active = false;
			}
		}
	}
}

void UI::Draw(Renderer* renderer, bool enableLight)
{
	renderer->RenderMeshOnScreen(tempMeshList->GetMesh(MeshList::MESH_STAMINABAR), 40, 10, staminaBar_width, 1);

	if (camera->GetSprintState() == false)		//Walking
	{
		text[0]->Draw(renderer, enableLight);
	}
	else										//Sprinting
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

bool UI::getCamSprintState()
{
	return camera->GetSprintState();
}

GameObject* UI::getItem()
{
	return Item;
}

void UI::setCamera(CameraVer2* camera)
{
	this->camera = camera;
}

void UI::setCamSprintState(bool isSprinting)
{
	camera->SetSprintState(isSprinting);
}

void UI::setItem(GameObject* item)
{
	this->Item = item;
}

void UI::setInteractable(bool interactable)
{
	this->interactable = interactable;
}