#include "SceneTrain.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

SceneTrain::SceneTrain() :
	fps(0.f)
{
}

SceneTrain::~SceneTrain()
{
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

	MainChar = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_CUBE));
	MainChar->SetColliderBox();
	MainChar->Init(Vector3(0, 3, -40));
	MainChar->SetTranslate(MainChar->GetTranslate() + Vector3(0,30,0));
	//MainChar->SetCamera(&camera);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Cube[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));

	Cube[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[1]->SetColliderBox();

	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(Vector3(0, 0, 5), Vector3(0, 0, 0));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.8f, 2.f, 0.8f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);

	ui = new UI();
	ui->Init(Ayaka);
	ui->setCamera(&camera);


	npc = goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_NPC));
	npc->Init(meshlist, Ayaka, Vector3(2, 0, 2));

	train = goManager.CreateGO<Train>(meshlist->GetMesh(MeshList::MESH_TRAIN));
	train->Init(meshlist, Ayaka);
	train->SetDefaultPos(Vector3(0, 2, -5));
	train->PushStop(0, 2, -10);
	train->PushStop(5,2,5)->SetStation();
	train->ExtendStop(20)->ExtendStop(0,0,14);
	train->PushStop(0, 2, 0);

	{
		Environment[EN_FLOOR1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
		Environment[EN_FLOOR1]->SetScale(Vector3(30, 30, 30));
		Environment[EN_FLOOR1]->SetRotate(Vector3(0, 180, 0));

		//Environment[EN_COUNTER] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
		//Environment[EN_COUNTER]->SetColliderBox(Vector3(15, 1.25, 0.5));
		//Environment[EN_COUNTER]->SetScale(Vector3(30, 2.5, 1));
		//Environment[EN_COUNTER]->SetTranslate(Vector3(0, 1.125, -10));
	}
}

void SceneTrain::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 50, 80), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -50, -80));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_POINT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneTrain::Update(double dt)
{
	if (!bPauseGame)
	{
		camera.Updatemovement(dt);

		train->UpdateChildCollision();
		//Collision


		Ayaka->CollisionResolution(train);
		train->Update(dt);

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

		// Cube Collision Test stuff
		{
			float SPEED = 5.f * dt;
			Vector3 Direction = Vector3(0, 0, 0);
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

			if (Application::IsKeyPressed('T'))
			{
				Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(SPEED * 10, 0, 0));
			}
			if (Application::IsKeyPressed('G'))
			{
				Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(-SPEED * 10, 0, 0));
			}
			if (Application::IsKeyPressed('F'))
			{
				Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, 0, -SPEED * 10));
			}
			if (Application::IsKeyPressed('H'))
			{
				Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, 0, SPEED * 10));
			}
			if (Application::IsKeyPressed('R'))
			{
				Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, SPEED * 10, 0));
			}
			if (Application::IsKeyPressed('Y'))
			{
				Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, -SPEED * 10, 0));
			}
			 
			Cube[0]->SetTranslate(Cube[0]->GetTranslate() + Direction * SPEED);
		}
		Ayaka->IsWithinRangeOf(npc);
		npc->Update(dt);
	}

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
	train->Draw(renderer, true);
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
