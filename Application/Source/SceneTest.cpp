#include "SceneTest.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

SceneTest::SceneTest() :
	fps(0.f)
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
{
	isInit = true;
	x_width = 30;
	mapOpen = false;

	//Init Meshlist and texture 
	MeshList* meshlist = MeshList::GetInstance();
	//Create Light
	lights[0] = new Light(renderer->GetprogramID(), 0);

	camera.Init(Vector3(0, 3, 8), Vector3(0, 0, -1), Vector3(0, 1, 0));

	character = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_QUAD));
	camera.SetTarget(character);

	ui = new UI();
	ui->Init(character);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Quad = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
	Quad->SetScale(Vector3(20, 20, 20));

	Item[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Item[0]->SetTranslate(Vector3(3, 3, 0));

	Item[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Item[1]->SetTranslate(Vector3(-6, 3, 2));
	
	Item[2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Item[2]->SetTranslate(Vector3(8, 3, -4));

	//Init the Skybox
	skybox = new Skybox(goManager, meshlist);


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
	text[4] = new Text();
	text[4]->SetMode(Text::STATIC_SCREENTEXT);
	text[4]->SetText("Item Acquired.");
	text[4]->SetTranslate(Vector3(27.5, 12.5, 0));

}

void SceneTest::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[0]->Set(Light::LIGHT_POINT,
				Vector3(0, 10, 0),
				Color(1, 1, 1),
				1.f, 1.f, 0.01f, 0.001f,
				Vector3(0.f, 1.f, 0.f));
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
	


	if (Application::IsKeyPressed('E') && ui->getInteractable() == true)
	{
		setQuestStatus(true);
	}
	if (getQuestStatus() == false)
	{
		std::cout << "Scene2 Quest inactive." << std::endl;
	}
	else
	{
		std::cout << "Scene2 Quest active." << std::endl;
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
	renderer->LoadIdentity();

	//Camera
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());
	//Light
	renderer->SetLight(lights[0], camera.GetPosition());

	Axis->Draw(renderer, false);

	//Skybox
	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}

	Quad->Draw(renderer, true);

	//Proximity
	for (int i = 0; i < sizeof(Item) / sizeof(Item[0]); i++)
	{
		Item[i]->Draw(renderer, true);

		ui->setItem(Item[i]);

		if (character->GetInRange(Item[i], 3))
		{
			ui->setInteractable(true);
			ui->UpdateInteractions(Item[i]);
		}
		else {
			ui->setInteractable(false);
			ui->UpdateInteractions(Item[i]);
		}
	}

	
	
	//FPS
	text[0]->Draw(renderer, false);

	ui->Draw(renderer, true);
}

void SceneTest::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneTest::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
