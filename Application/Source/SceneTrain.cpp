#include "SceneTrain.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"
#include "SceneManager.h"
SceneTrain::SceneTrain() :
	fps(0.f)
{
}

SceneTrain::~SceneTrain()
{
	if (SceneManager::getCurrentSceneType() == SceneManager::SCENE_TRAIN)
		delete renderer;

	delete ui;
	delete Axis;
	delete Ayaka;
	delete train;
	delete traincollider;
	delete npc;
	delete skybox;

	for (int enIdx = 0; enIdx < EN_TOTAL; enIdx++)
	{
		delete Environment[enIdx];
	}
	for (int LtIdx = 0; LtIdx < LIGHT_TOTAL; LtIdx++)
	{
		delete lights[LtIdx];
	}
	for (int WPIdx = 0; WPIdx < WP_TOTAL; WPIdx++)
	{
		delete Waypoints[WPIdx];
	}
}

void SceneTrain::Init()
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
	
	//point all Environment to NULL for unused environment enums
	for (int i = 0; i < EN_TOTAL; i++) {
		Environment[i] = NULL;
	}

	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(Vector3(0, 2, 100), Vector3(0, 0, 0));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.8f, 2.f, 0.8f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);
	camera.SetClamp(Vector3(148, 400, 148));

	ui = new UI();
	ui->Init(Ayaka);

	npc = goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_NPC));
	npc->Init(meshlist, Ayaka, Vector3(5, 3, 98), Vector3(0, 330, 0));
	npc->SetUI(ui);
	npc->SetColliderBox();
	npc
		->PushText("Welcome to the train station!")
		->PushText("Hop into the train and get an amazing view of our city!")
	;

	train = goManager.CreateGO<Train>(meshlist->GetMesh(MeshList::MESH_TRAIN));
	train->Init(meshlist, Ayaka);
	train->SetDefaultPos(Vector3(0, 1.85, 90));
	train->ExtendStop(80)
		->ExtendStop(20, 0, -20)
		->ExtendStop(0, 0, -160)
		->ExtendStop(-20, 0, -20)
		->ExtendStop(-160,0,0)
		->ExtendStop(-20, 0, 20)
		->ExtendStop(0, 0, 160)
		->ExtendStop(20, 0, 20)
		->ExtendStop(30)
		->ExtendStop(15)
		->ExtendStop(35)
		->SetStation()
		;


	traincollider = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	traincollider->SetActive(false);
	traincollider->SetColliderBox(Vector3(4.5, 5, 3), Vector3(0, 4.5, 0));
	traincollider->SetTranslate(train->GetTranslate());
	{
		Environment[EN_FLOOR1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_GRASS));
		Environment[EN_FLOOR1]->SetScale(Vector3(300, 300, 300));
		Environment[EN_FLOOR1]->SetRotate(Vector3(0, 180, 0));

		//Environment
		Environment[EN_PLATFORM] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PLATFORM));
		Environment[EN_PLATFORM]->SetScale(Vector3(40, 2, 20));
		Environment[EN_PLATFORM]->SetColliderBox(Vector3(20, 1, 10));
		Environment[EN_PLATFORM]->SetTranslate(Vector3(0, 2, 105));

		Environment[EN_TOWER] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PAGODA));
		Environment[EN_TOWER]->SetColliderBox(Vector3(29, 3, 29), Vector3(2, 2.4f, 0)); //Platform
		Environment[EN_TOWER]->SetColliderBox(Vector3(15, 40, 15), Vector3(0, 40, 0)); //Pagoda
		Environment[EN_TOWER]->SetColliderBox(Vector3(7, 3, 1), Vector3(31.6f, 1.4, 0)); //Stairs
		Environment[EN_TOWER]->SetColliderBox(Vector3(7, 3, 1), Vector3(33.5f, 0, 0));
		Environment[EN_TOWER]->SetColliderBox(Vector3(7, 3, 1), Vector3(35.5f, -1.4f, 0));


		for (int i = EN_TREE; i < EN_ENDTREES; i++) { //Set all 13 trees to have the same tree mesh
			Environment[i] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TREE));
			float randomscale = std::rand() % 4 + 15;

			Environment[i]->SetScale(Vector3(randomscale, randomscale, randomscale));
		}

		//
		Environment[EN_TREE]->SetTranslate(Vector3(35,0,-35));
		Environment[EN_TREEBOTL1]->SetTranslate(Vector3(-34, 0 , 50));
		Environment[EN_TREEBOTL2]->SetTranslate(Vector3(-60, 0 , 10));
		Environment[EN_TREEBOTL3]->SetTranslate(Vector3(-13, 0, 80));
		Environment[EN_TREEBOTR1]->SetTranslate(Vector3(20, 0, 40));
		Environment[EN_TREEBOTR2]->SetTranslate(Vector3(60, 0, 60));
		Environment[EN_TREEBOTR3]->SetTranslate(Vector3(90, 0, -5));
		Environment[EN_TREETOPR1]->SetTranslate(Vector3(35, 0, -70));
		Environment[EN_TREETOPR2]->SetTranslate(Vector3(50, 0, -30));
		Environment[EN_TREETOPR3]->SetTranslate(Vector3(4, 0, -55));
		Environment[EN_TREETOPL1]->SetTranslate(Vector3(-5, 0, -90 ));
		Environment[EN_TREETOPL2]->SetTranslate(Vector3(-90, 0, -50));
		Environment[EN_TREETOPL3]->SetTranslate(Vector3(-70, 0, -10));

	}

	Waypoints[WP_DOOR] = new WayPoint("City", Vector3(0, 1, 12));
	Waypoints[WP_DOOR]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
	Waypoints[WP_DOOR]->SetRotate(Vector3(0, 180, 0));
	Waypoints[WP_DOOR]->SetTranslate(Vector3(0, 2, 110));
}

void SceneTrain::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 50, 80), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -50, -80));
	lights[1]->Set(Light::LIGHT_POINT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneTrain::Update(double dt)
{
	if (!bPauseGame)
	{
		camera.Updatemovement(dt);



		train->UpdateChildCollision();
		train->UpdateCollision();
		//Collision


		Ayaka->CollisionResolution(train);

		
		bool insideTrain = 
			traincollider->GetColliderBox(0)
			->CheckOBBCollision(Ayaka->GetColliderBox(0)).Collided;

		train->SetTransparentCollider(insideTrain);
		train->Update(dt);
		traincollider->SetTranslate(train->GetTranslate());
		traincollider->SetRotate(train->GetRotate());
		for (int i = EN_PLATFORM; i < EN_ENDTREES; i++)
			Ayaka->CollisionResolution(Environment[i]);
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
		Ayaka->Update(dt);
		npc->Update(dt);
	}

	Waypoints[WP_DOOR]->inRangeResponse(Ayaka, SceneManager::SCENE_CITY);
	camera.Updateposition();
	ui->Update(dt);
}

void SceneTrain::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());
	renderer->SetToProj();
	for (int i = 0; i < 2; i++)
		renderer->SetLight(lights[i], camera.GetPosition());
	//renderer->SetLight(lights[1]);

	Axis->Draw(renderer, false);

	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}

	for (int i = 0; i < EN_TOTAL; i++) {
		if (Environment[i]) {
			Environment[i]->Draw(renderer, true);
		}
	}
	Ayaka->Draw(renderer, true);
	npc->Draw(renderer, true);
	for (int i = 0; i < WP_TOTAL; i++)
	{
		if (Waypoints[i])
		{
			Waypoints[i]->Draw(renderer, false);
			Waypoints[i]->DrawLocName(renderer);

		}
	}
	train->Draw(renderer, true);
	traincollider->Draw(renderer, false);
	ui->Draw(renderer, true);

}

void SceneTrain::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneTrain::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
