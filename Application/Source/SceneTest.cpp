#include "SceneTest.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"

SceneTest::SceneTest() :
	fps(0.f)
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
{
	x_width = 30;
	mapOpen = false;

	renderer = new Renderer();
	//Init Meshlist
	meshlist = new MeshList();
	//Create Light
	lights[0] = new Light(renderer->GetprogramID(), 0);
	
	ui = new UI();
	ui->Init();

	camera.Init(Vector3(0, 3, 8), Vector3(0, 0, -1), Vector3(0, 1, 0));
	


	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Quad = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
	Quad->SetScale(Vector3(20, 20, 20));

	Item[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Item[0]->SetTranslate(Vector3(3, 3, 0));
	
	Item[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Item[1]->SetTranslate(Vector3(-6, 3, 2));

	character =  goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_QUAD));

	//FPS Render
	std::ostringstream ss;
	ss << "FPS: " << fps;
	text[0] = new Text();
	text[0]->SetMode(Text::STATIC_SCREENTEXT);
	text[0]->SetText(ss.str());
	text[0]->SetTranslate(Vector3(0.f, 0, 0));	

	////Status: Walking
	//text[1] = new Text();
	//text[1]->SetMode(Text::STATIC_SCREENTEXT);
	//text[1]->SetText("Walking");
	//text[1]->SetTranslate(Vector3(0.f, 4, 0));	
	//
	////Status: Sprinting
	//text[2] = new Text();
	//text[2]->SetMode(Text::STATIC_SCREENTEXT);
	//text[2]->SetText("Sprinting");
	//text[2]->SetTranslate(Vector3(0.f, 4, 0));
	
	//Interaction

	{
	lights[0]->Set(Light::LIGHT_POINT,
		           Vector3(0, 8, 0),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));
	}
}	

void SceneTest::Update(double dt)
{
	fps = 1.f / dt;

	static bool bLButtonState = false;
	//Debug controls
	{
		if (Application::IsKeyPressed('1'))
		{
			glEnable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('2'))
		{
			glDisable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('3'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (Application::IsKeyPressed('4'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		//Input
		if (Application::IsKeyPressed('9'))
		{
			Application::EnableCursor();
		}
		if (Application::IsKeyPressed('0'))
		{
			Application::DisableCursor();
		}

		if (Application::IsKeyPressed('M'))
		{
			mapOpen = !mapOpen;
		}

	}

	camera.Updatemovement(dt);
	ui->setCamera(&camera);
	ui->Update();
	//ui->setCamSprintState(&camera);

	//LMB Click
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}

	//Stamina Bar
	/*camera.SetSprintState(false);*/

	character->SetTranslate(camera.GetPosition());

	//FPS Update
	std::ostringstream ss;
	ss << "FPS: " << fps;
	text[0]->SetText(ss.str());


	//std::cout << "Collectible Count: " + std::to_string(character->getCollectibleCount()) << std::endl;
}

void SceneTest::Render()
{
	renderer->Reset();

	//Camera
	renderer->SetCamera(camera);


	Axis->Draw(renderer, false);
	Quad->Draw(renderer, true);

	//Proximity
	for (int i = 0; i < sizeof(Item) / sizeof(Item[0]); i++)
	{
		Item[i]->Draw(renderer, true);

		//character.interactWith(item[i]);

		//if (character->IsWithinRangeOf(Item[i]))
		//{
		//	if (Item[i]->getActive() == true) //text to pickup item
		//		text[3]->Draw(renderer, true);
		//	else
		//		text[4]->Draw(renderer, true);

		//	//TODO: Shift functionality from current scene over to character
		//	if (Application::IsKeyPressed('E')) //code to stop rendering item once it has been picked up
		//	{
		//		if (Item[i]->getActive())
		//		{
		//			Item[i]->SetActive(false);
		//			character->IncrementCollectible();
		//		}
		//		//TODO: Delete item from world once it has been picked up
		//	}
		//}
	}

	//2D Real-Time Map
	if (mapOpen == false)
	{
		//renderer->RenderMeshOnScreen(meshlist->GetMesh(MeshList::MESH_STAMINABAR), 40, 10, x_width, 1);
	}
	else
	{
		renderer->RenderMeshOnScreen(meshlist->GetMesh(MeshList::MESH_QUAD), 40, 30, 50, 50);
		renderer->RenderMeshOnScreen(meshlist->GetMesh(MeshList::MESH_ICON), 40 + camera.GetPosX(), 30 - camera.GetPosZ(), 1, 1);
	}

	//Light
	renderer->SetLight(lights[0]);
	
	//FPS
	text[0]->Draw(renderer, false);

	//UI (Render UI last to ensure text is properly rendered on screen)
	ui->Draw(renderer, true);
}

void SceneTest::Exit()
{
}

void SceneTest::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
