#include "UI.h"
#include "Application.h"

#include <sstream>

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
	max_X = 30;
	max_Z = 30;

	interactable = false;
	mapOpen = false;
	Dialogue = false;

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
	
	text[3] = new Text();
	text[3]->SetMode(Text::STATIC_SCREENTEXT);
	text[3]->SetTranslate(Vector3(108, 68, 0));

	////Dialogue for everything

	//Characters
	text[4] = new Text();
	text[4]->SetMode(Text::STATIC_SCREENTEXT);
	text[4]->SetText("Ayaka:");
	text[4]->SetTranslate(Vector3(0.f, 16, 0));

	text[5] = new Text();
	text[5]->SetMode(Text::STATIC_SCREENTEXT);
	text[5]->SetText("City Mayor:");
	text[5]->SetTranslate(Vector3(0.f, 16, 0));

	text[6] = new Text();
	text[6]->SetMode(Text::STATIC_SCREENTEXT);
	text[6]->SetText("The Librarian:");
	text[6]->SetTranslate(Vector3(0.f, 16, 0));

	//Dialogue
	text[7] = new Text();
	text[7]->SetMode(Text::STATIC_SCREENTEXT);
	text[7]->SetText("Uh... Damn it. Spatial Vortexes are the worst. Where is this place even?");
	text[7]->SetTranslate(Vector3(0.f, 13, 0));

	text[8] = new Text();
	text[8]->SetMode(Text::STATIC_SCREENTEXT);
	text[8]->SetText("Hmm... From the looks of it, it would seem that I have landed on a Spatial Outpost.");
	text[8]->SetTranslate(Vector3(0.f, 13, 0));
		 
}

void UI::Update()
{
	staminaBar_width = Player->getStamina() / 2;

	if (Application::IsKeyPressed('M') && !KeyPressed)
	{
		KeyPressed = true;
		mapOpen = !mapOpen;
	}
	else if(!Application::IsKeyPressed('M') && KeyPressed)
	{
		KeyPressed = false;
	}

	if (Application::IsKeyPressed('T') && !KeyPressed)
	{
		Dialogue = !Dialogue;
		KeyPressed = true;
	}
	else if (!Application::IsKeyPressed('T') && KeyPressed)
	{
	//	KeyPressed = false;
	}

	std::stringstream collCount;
	collCount << "Collectibles: " << Player->getCollectibleCount();
	text[3]->SetText(collCount.str());
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
				Player->IncrementCollectible();
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
	if (!Dialogue)
	{
		if (mapOpen == false)
		{
			//render stamina bar if map is not open
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_STAMINABAR), 64, 10, staminaBar_width, 1);
		}
		else
		{
			//render map
			float x_offset = round(35 * (Player->GetTranslate().x / getMapBoundsX()));	//half of quad's size * (player's pos/30)
			float z_offset = round(35 * (Player->GetTranslate().z / getMapBoundsZ()));

			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_QUAD), 64, 36, 70, 70);
			renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_ICON), 64 + x_offset, 36 - z_offset, 1, 1);
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

		text[3]->Draw(renderer, true);
	}
	else
	{
		renderer->RenderMeshOnScreen(MeshList::GetInstance()->GetMesh(MeshList::MESH_DIALOGUEBOX), 64, 10, 128, 20);
		text[4]->Draw(renderer, true);
		text[7]->Draw(renderer, true);
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

float UI::getMapBoundsX()
{
	return max_X;
}

float UI::getMapBoundsZ()
{
	return max_Z;
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

void UI::setMapBounds(float max_X, float max_Z)
{
	this->max_X = max_X;
	this->max_Z = max_Z;
}

