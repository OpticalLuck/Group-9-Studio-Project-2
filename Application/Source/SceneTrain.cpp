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
	
	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(Vector3(0, 2, 100), Vector3(0, 0, 0));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.8f, 2.f, 0.8f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);

	ui = new UI();
	ui->Init(Ayaka);

	npc = goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_NPC));
	npc->Init(meshlist, Ayaka, Vector3(2, 0, 2));


	train = goManager.CreateGO<Train>(meshlist->GetMesh(MeshList::MESH_TRAIN));
	train->Init(meshlist, Ayaka);
	train->SetDefaultPos(Vector3(0, 2, -5));
	train->PushStop(0, 2, -10);
	train->PushStop(5,2,5)->SetStation();
	train->ExtendStop(20)->ExtendStop(0,0,14);
	train->ExtendStop(15, 0, 0);


	traincollider = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	traincollider->SetActive(false);
	traincollider->SetColliderBox(Vector3(4.5, 5, 3), Vector3(0, 4.5, 0));
	traincollider->SetTranslate(train->GetTranslate());
	{
		Environment[EN_FLOOR1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_GRASS));
		Environment[EN_FLOOR1]->SetScale(Vector3(300, 300, 300));
		Environment[EN_FLOOR1]->SetRotate(Vector3(0, 180, 0));

		//Environment
	}

	Waypoints[WP_DOOR] = new WayPoint("City", Vector3(0, 1, 12));
	Waypoints[WP_DOOR]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
	Waypoints[WP_DOOR]->SetRotate(Vector3(0, 180, 0));
	Waypoints[WP_DOOR]->SetTranslate(Vector3(0, 0, 110));
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

		
		bool insideTrain = traincollider->GetColliderBox(0)->CheckOBBCollision(Ayaka->GetColliderBox(0)).Collided;
		train->SetTransparentCollider(insideTrain);
		train->Update(dt);
		traincollider->SetTranslate(train->GetTranslate());
		traincollider->SetRotate(train->GetRotate());
		//Ayaka->CollisionResolution(train->getDoor());
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


	Environment[EN_FLOOR1]->Draw(renderer, true);

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
