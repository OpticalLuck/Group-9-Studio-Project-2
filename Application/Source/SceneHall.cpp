#include "SceneHall.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

SceneHall::SceneHall() :
	fps(0.f)
{
}

SceneHall::~SceneHall()
{
	if (SceneManager::getCurrentSceneType() == SceneManager::SCENE_HALL)
		delete renderer;

	delete ui;
	delete Character_Name[0];
	delete Axis;
	delete Ayaka;
	delete npc;
	delete Collectible;
	delete skybox;
	delete Interaction[0];
	for (int ENIdx = 0; ENIdx < EN_TOTAL; ENIdx++)
	{
		delete Environment[ENIdx];
	}
	for (int WPIdx = 0; WPIdx < WP_TOTAL; WPIdx++)
	{
		delete Waypoints[WPIdx];
	}
	for (int LtIdx = 0; LtIdx < LIGHT_TOTAL; LtIdx++)
	{
		delete lights[LtIdx];
	}
}

void SceneHall::Init()
{
	isInit = true;
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 3, -40), Vector3(0, 0, -1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	MeshList* meshlist = MeshList::GetInstance();

	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);
	lights[1] = new Light(Shader::GetInstance()->shaderdata, 1);

	skybox = new Skybox(goManager, meshlist, 3);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));

	Collectible = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_KEY));
	Collectible->SetScale(Vector3(3, 3, 3));
	Collectible->SetTranslate(Vector3(0, 3, 0));

	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(Vector3(0, 0, 5), Vector3(0, 0, 0));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.8f, 2.f, 0.8f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);

	npc = goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_NPC));
	npc->SetColliderBox(Vector3(0.5, 1, 0.5), Vector3(0, 2, 0));
	npc->Init(meshlist, Ayaka, Vector3(0, 1.5f, -3), Vector3(0, 0, 0));
	//npc->PushPathPoint(Vector3(4, 3, 0));
	//npc->PushPathPoint(Vector3(0, 3, -9));

	ui = new UI();
	ui->Init(Ayaka);

	Character_Name[0] = new Text();
	Character_Name[0]->SetMode(Text::STATIC_WORLDTEXT);
	Character_Name[0]->SetText("City Mayor Mariano");
	Character_Name[0]->SetTranslate(Vector3(-3, 6, -3));

	Interaction[0] = new Text();
	Interaction[0]->SetMode(Text::STATIC_SCREENTEXT);
	Interaction[0]->SetText("Press E to Interact");
	Interaction[0]->SetTranslate(Vector3(50, 12.5, 0));

	{
		Environment[EN_FLOOR1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR1]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR1]->SetRotate(Vector3(0, 180, 0));

		Environment[EN_FLOOR2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_INDOORWALL));
		Environment[EN_FLOOR2]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR2]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR2]->SetTranslate(Vector3(0, 0, -15));
		Environment[EN_FLOOR2]->SetRotate(Vector3(90, 0, 0));

		Environment[EN_FLOOR3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_INDOORWALL));
		Environment[EN_FLOOR3]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR3]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR3]->SetTranslate(Vector3(0, 0, 15));
		Environment[EN_FLOOR3]->SetRotate(Vector3(90, 180, 0));

		Environment[EN_FLOOR4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_INDOORWALL));
		Environment[EN_FLOOR4]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR4]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR4]->SetTranslate(Vector3(15, 0, 0));
		Environment[EN_FLOOR4]->SetRotate(Vector3(0, -90, 90));

		Environment[EN_FLOOR5] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_INDOORWALL));
		Environment[EN_FLOOR5]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR5]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR5]->SetTranslate(Vector3(-15, 0, 0));
		Environment[EN_FLOOR5]->SetRotate(Vector3(0, 90, 270));

		Environment[EN_FLOOR6] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR6]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR6]->SetTranslate(Vector3(0, 15, 0));
		Environment[EN_FLOOR6]->SetRotate(Vector3(180, 0, 0));

		Environment[EN_TABLE] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TABLE));
		Environment[EN_TABLE]->SetColliderBox(Vector3(4, 2.5, 1.6));
		Environment[EN_TABLE]->SetScale(Vector3(2, 2.5, 1.5));
		Environment[EN_TABLE]->SetTranslate(Vector3(0, 0.025, 0));
		
		Environment[EN_PLANT1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT1]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT1]->SetTranslate(Vector3(14, 0, 14));

		Environment[EN_PLANT2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT2]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT2]->SetTranslate(Vector3(-14, 0, 14));

		Environment[EN_PLANT3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT3]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT3]->SetTranslate(Vector3(-14, 0, -14));

		Environment[EN_PLANT4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT4]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT4]->SetTranslate(Vector3(14, 0, -14));

		Environment[EN_PORTAL] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PORTAL));
		Environment[EN_PORTAL]->SetScale(Vector3(4, 4, 4));
		Environment[EN_PORTAL]->SetRotate(Vector3(90, 1, 1));
		Environment[EN_PORTAL]->SetTranslate(Vector3(0, 3, -14.5));

		Waypoints[WP_DOOR] = new WayPoint("City", Vector3(0, 1, 12));
		Waypoints[WP_DOOR]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
		Waypoints[WP_DOOR]->SetRotate(Vector3(0, 180, 0));

		Waypoints[WP_PORTAL] = new WayPoint("Portal", Vector3(0, 1, -14));
		Waypoints[WP_PORTAL]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
		//Waypoints[WP_PORTAL]->SetRotate(Vector3(0, 180, 0));
	}

	for (int i = 0; i < WP_TOTAL; i++) {
		Waypoints[i]->SetActive(false);
	}

}

void SceneHall::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 50, 80), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -50, -80));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_POINT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneHall::Update(double dt)
{
	//have something else update teh cam. to have access to both cam and character
	if (!bPauseGame)
	{

		camera.Updatemovement(dt);
		Ayaka->Update(dt);

	//Collision
	Ayaka->CollisionResolution(Environment[EN_FLOOR2]);
	Ayaka->CollisionResolution(Environment[EN_FLOOR3]);
	Ayaka->CollisionResolution(Environment[EN_FLOOR4]);
	Ayaka->CollisionResolution(Environment[EN_FLOOR5]);
	Ayaka->CollisionResolution(Environment[EN_TABLE]);
	Ayaka->CollisionResolution(Environment[EN_PLANT1]);
	Ayaka->CollisionResolution(Environment[EN_PLANT2]);
	Ayaka->CollisionResolution(Environment[EN_PLANT3]);
	Ayaka->CollisionResolution(Environment[EN_PLANT4]);
	Ayaka->CollisionResolution(npc);

	Waypoints[WP_DOOR]->inRangeResponse(Ayaka, SceneManager::SCENE_CITY);

	if (portalOpen == true)
	{
		Waypoints[WP_PORTAL]->inRangeResponse(Ayaka, SceneManager::SCENE_MAINMENU); //change to end screen later

		if (Waypoints[WP_PORTAL]->inRangeResponse(Ayaka, SceneManager::SCENE_MAINMENU) && Application::IsKeyPressed('E'))
		{
			SceneManager::ChangeScene(SceneManager::SCENE_GAMEOVER);
		}
	}

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

			if (Application::IsKeyPressed('9'))
			{
				Collision::isRender = true;
			}
			if (Application::IsKeyPressed('0'))
			{
				Collision::isRender = false;
			}
		}

		// Cube Collision Test stuff
		{
			float SPEED = 5.f * dt;
			Vector3 Direction = Vector3(0,0,0);
			if (Application::IsKeyPressed('I'))
				Direction += Vector3(0, 0, 1);
			if (Application::IsKeyPressed('K'))
				Direction += Vector3(0, 0, -1);
			if (Application::IsKeyPressed('J'))
				Direction += Vector3(1, 0, 0);
			if (Application::IsKeyPressed('L'))
				Direction += Vector3(-1, 0, 0);
			if (Application::IsKeyPressed('O'))
				Direction += Vector3(0, 1, 0);
			if (Application::IsKeyPressed('P'))
				Direction += Vector3(0, -1, 0);

			if (Application::IsKeyPressed('E') && ui->getInteractable() == true)
			{
				portalOpen = true;
			}
	}

		Ayaka->IsWithinRangeOf(npc);
		npc->Update(dt);
	}

	camera.Updateposition();
	ui->Update(dt);

}

void SceneHall::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());
	renderer->SetToProj();
	for (int i = 0; i < 2; i++)
		renderer->SetLight(lights[i], camera.GetPosition());
	//renderer->SetLight(lights[1]);

	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}


	Character_Name[0]->Draw(renderer, true);

	Environment[EN_FLOOR1]->Draw(renderer, true);
	Environment[EN_FLOOR2]->Draw(renderer, true);
	Environment[EN_FLOOR3]->Draw(renderer, true);
	Environment[EN_FLOOR4]->Draw(renderer, true);
	Environment[EN_FLOOR5]->Draw(renderer, true);
	Environment[EN_FLOOR6]->Draw(renderer, true);
	Environment[EN_TABLE]->Draw(renderer, true);
	Environment[EN_PLANT1]->Draw(renderer, true);
	Environment[EN_PLANT2]->Draw(renderer, true);
	Environment[EN_PLANT3]->Draw(renderer, true);
	Environment[EN_PLANT4]->Draw(renderer, true);

	if (portalOpen == true)
	{
		Environment[EN_PORTAL]->Draw(renderer, false);
	}

	if (Ayaka->GetInRange(Environment[EN_TABLE], 4))
	{
		Interaction[0]->Draw(renderer, true);
	}
	else
	{

	}

	//Environment[EN_HOUSE5]->Draw(renderer, true);

	//Environment[EN_TOWER1]->Draw(renderer, true);

	Ayaka->Draw(renderer, true);
	
	npc->Draw(renderer, true);

	
	if (getQuestStatus() == true) //if all other quests are completed (this scene's quest status set to true from SceneManager), render final item to collect in order for game to end
	{
		Collectible->Draw(renderer, true);

		ui->setItem(Collectible);
		if (Ayaka->GetInRange(Collectible, 4))
		{
			ui->setInteractable(true);
			ui->UpdateInteractions(Collectible);
		}
		else
		{
			ui->setInteractable(false);
			ui->UpdateInteractions(Collectible);
		}
	}

	for (int i = 0; i < WP_TOTAL; i++)
	{
		if (Waypoints[i])
		{
			if (i != WP_PORTAL || portalOpen)
			{
				Waypoints[i]->Draw(renderer, false);
				Waypoints[i]->DrawLocName(renderer);
			}
		}
	}

	ui->Draw(renderer, true);
}

void SceneHall::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneHall::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
