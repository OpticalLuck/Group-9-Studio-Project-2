#include "SceneLibrary.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

SceneLibrary::SceneLibrary() :
	fps(0.f)
{
}

SceneLibrary::~SceneLibrary()
{
	if (SceneManager::getCurrentSceneType() == SceneManager::SCENE_LIBRARY)
		delete renderer;

	delete Ayaka;
	delete Collectible;
	delete skybox;
	delete npc;
	delete Character_Name[0];
	delete ui;
	delete Interaction[0];
	for (int enIdx = 0; enIdx < EN_TOTAL; enIdx++)
	{
		delete Environment[enIdx];
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

void SceneLibrary::Init()
{
	isInit = true;
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 3, -40), Vector3(0, 0, -1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	MeshList* meshlist = MeshList::GetInstance();

	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);
	lights[1] = new Light(Shader::GetInstance()->shaderdata, 1);

	skybox = new Skybox(goManager, meshlist, 3);

	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(Vector3(0, 0, 5), Vector3(0, 0, 0));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.8f, 2.f, 0.8f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);

	Collectible = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_GEM));
	Collectible->SetScale(Vector3(3, 3, 3));

	ui = new UI();
	ui->Init(Ayaka);

	npc = goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_NPC));
	//Please use the init to apply any initial transformations (position, rotation, scale, radius)
	npc->Init(meshlist, Ayaka, Vector3(0, 0, -12));
	npc->SetColliderBox(Vector3(0.5f, 3.f, 0.5f));
	

	Character_Name[0] = new Text();
	Character_Name[0]->SetMode(Text::STATIC_WORLDTEXT);
	Character_Name[0]->SetText("Librarian Morisu");
	Character_Name[0]->SetTranslate(Vector3(-2.5, 4, -12));

	Interaction[0] = new Text();
	Interaction[0]->SetMode(Text::STATIC_SCREENTEXT);
	Interaction[0]->SetText("Press E to Interact");
	Interaction[0]->SetTranslate(Vector3(50, 12.5, 0));

	{
		Environment[EN_FLOOR1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR1]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR1]->SetRotate(Vector3(0, 180, 0));

		Environment[EN_FLOOR2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR2]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR2]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR2]->SetTranslate(Vector3(0, 0, -15));
		Environment[EN_FLOOR2]->SetRotate(Vector3(90, 0, 0));

		Environment[EN_FLOOR3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR3]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR3]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR3]->SetTranslate(Vector3(0, 0, 15));
		Environment[EN_FLOOR3]->SetRotate(Vector3(90, 180, 0));

		Environment[EN_FLOOR4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR4]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR4]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR4]->SetTranslate(Vector3(15, 0, 0));
		Environment[EN_FLOOR4]->SetRotate(Vector3(0, 0, 90));

		Environment[EN_FLOOR5] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR5]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR5]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR5]->SetTranslate(Vector3(-15, 0, 0));
		Environment[EN_FLOOR5]->SetRotate(Vector3(0, 0, 270));

		Environment[EN_FLOOR6] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR6]->SetColliderBox(Vector3(15, 0, 15));
		Environment[EN_FLOOR6]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR6]->SetTranslate(Vector3(0, 15, 0));
		Environment[EN_FLOOR6]->SetRotate(Vector3(180, 0, 0));

		Environment[EN_COUNTER] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE2));
		Environment[EN_COUNTER]->SetColliderBox(Vector3(15, 1.25, 0.5));
		Environment[EN_COUNTER]->SetScale(Vector3(30, 2.5, 0.9));
		Environment[EN_COUNTER]->SetTranslate(Vector3(0, 1.125, -10));

		Environment[EN_TABLE1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TABLE));
		Environment[EN_TABLE1]->SetColliderBox(Vector3(4, 2.5, 1.6));
		Environment[EN_TABLE1]->SetScale(Vector3(2, 2.5, 1.5));
		Environment[EN_TABLE1]->SetTranslate(Vector3(10, 0.025, 7.5));
		Environment[EN_TABLE1]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_TABLE2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TABLE));
		Environment[EN_TABLE2]->SetColliderBox(Vector3(4, 2.5, 1.6));
		Environment[EN_TABLE2]->SetScale(Vector3(2, 2.5, 1.5));
		Environment[EN_TABLE2]->SetTranslate(Vector3(10, 0.025, -2.5));
		Environment[EN_TABLE2]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_TABLE3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TABLE));
		Environment[EN_TABLE3]->SetColliderBox(Vector3(4, 2.5, 1.6));
		Environment[EN_TABLE3]->SetScale(Vector3(2, 2.5, 1.5));
		Environment[EN_TABLE3]->SetTranslate(Vector3(-10, 0.025, 7.5));
		Environment[EN_TABLE3]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_TABLE4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TABLE));
		Environment[EN_TABLE4]->SetColliderBox(Vector3(4, 2.5, 1.6));
		Environment[EN_TABLE4]->SetScale(Vector3(2, 2.5, 1.5));
		Environment[EN_TABLE4]->SetTranslate(Vector3(-10, 0.025, -2.5));
		Environment[EN_TABLE4]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_PLANT1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT1]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT1]->SetTranslate(Vector3(14, 0, 14));

		Environment[EN_PLANT2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLANT));
		Environment[EN_PLANT2]->SetColliderBox(Vector3(1, 2, 1));
		Environment[EN_PLANT2]->SetTranslate(Vector3(-14, 0, 14));

		Waypoints[WP_DOOR] = new WayPoint("City", Vector3(0, 1, 12));
		Waypoints[WP_DOOR]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
		Waypoints[WP_DOOR]->SetRotate(Vector3(0, 180, 0));
	}

	for (int i = 0; i < WP_TOTAL; i++) {
		Waypoints[i]->SetActive(false);
	}

}

void SceneLibrary::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 50, 80), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -50, -80));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_POINT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneLibrary::Update(double dt)
{
	if (!bPauseGame)
	{

		camera.Updatemovement(dt);
		Ayaka->Update(dt);

		//Collision
		Ayaka->CollisionResolution(npc);

		Ayaka->CollisionResolution(Environment[EN_FLOOR1]);
		Ayaka->CollisionResolution(Environment[EN_FLOOR2]);
		Ayaka->CollisionResolution(Environment[EN_FLOOR3]);
		Ayaka->CollisionResolution(Environment[EN_FLOOR4]);
		Ayaka->CollisionResolution(Environment[EN_FLOOR5]);
		Ayaka->CollisionResolution(Environment[EN_FLOOR6]);
		Ayaka->CollisionResolution(Environment[EN_COUNTER]);
		Ayaka->CollisionResolution(Environment[EN_TABLE1]);
		Ayaka->CollisionResolution(Environment[EN_TABLE2]);
		Ayaka->CollisionResolution(Environment[EN_TABLE3]);
		Ayaka->CollisionResolution(Environment[EN_TABLE4]);
		Ayaka->CollisionResolution(Environment[EN_PLANT1]);
		Ayaka->CollisionResolution(Environment[EN_PLANT2]);

		Waypoints[WP_DOOR]->inRangeResponse(Ayaka, SceneManager::SCENE_CITY);
		
		if (Application::IsKeyPressed('E') && ui->getInteractable() == true)
		{
			setQuestStatus(true);
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

		Ayaka->IsWithinRangeOf(npc);
		npc->Update(dt);
	}
	camera.Updateposition();
	ui->Update(dt);
}

void SceneLibrary::Render()
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

	for (int i = 0; i < WP_TOTAL; i++)
	{
		if (Waypoints[i])
			Waypoints[i]->DrawLocName(renderer);
	}
	
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

	/*Cube[0]->Draw(renderer, false);
	Cube[1]->Draw(renderer, false);*/
	Character_Name[0]->Draw(renderer, true);

	Environment[EN_FLOOR1]->Draw(renderer, true);
	Environment[EN_FLOOR2]->Draw(renderer, true);
	Environment[EN_FLOOR3]->Draw(renderer, true);
	Environment[EN_FLOOR4]->Draw(renderer, true);
	Environment[EN_FLOOR5]->Draw(renderer, true);
	Environment[EN_FLOOR6]->Draw(renderer, true);
	Environment[EN_COUNTER]->Draw(renderer, true);
	Environment[EN_TABLE1]->Draw(renderer, true);
	Environment[EN_TABLE2]->Draw(renderer, true);
	Environment[EN_TABLE3]->Draw(renderer, true);
	Environment[EN_TABLE4]->Draw(renderer, true);
	Environment[EN_PLANT1]->Draw(renderer, true);
	Environment[EN_PLANT2]->Draw(renderer, true);


	Ayaka->Draw(renderer, true);
	npc->Draw(renderer, true);

	Waypoints[0]->Draw(renderer, false);

	if (Ayaka->GetInRange(Environment[EN_COUNTER], 4))
	{
		Interaction[0]->Draw(renderer, true);
	}
	else
	{

	}

	ui->Draw(renderer, true);
}

void SceneLibrary::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneLibrary::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
