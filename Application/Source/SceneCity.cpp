#include "SceneCity.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

#include "SceneManager.h"

SceneCity::SceneCity() :
	fps(0.f)
{
}

SceneCity::~SceneCity()
{
}

void SceneCity::Init()
{
	isInit = true; 
	bPauseGame = false;
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 5, -90), Vector3(0, 0, 1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);
	
	MeshList* meshlist = MeshList::GetInstance();

	skybox = new Skybox(goManager, meshlist, 3);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Cube[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[0]->SetTranslate(Vector3(0, 0, -80));
	Cube[0]->SetColliderBox(Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 0, 0));

	Cube[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[1]->SetTranslate(Vector3(0, 0, 1));
	Cube[1]->SetColliderBox(Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 0, 0));
	Cube[0]->AddChild(Cube[1]);
	
	Cube[2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[2]->SetTranslate(Vector3(0, 0, 1));
	Cube[2]->SetColliderBox(Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 0, 0));
	Cube[1]->AddChild(Cube[2]);
	
	Cube[3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[3]->SetTranslate(Vector3(0, 0, 1));
	Cube[3]->SetColliderBox(Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 0, 0));
	Cube[2]->AddChild(Cube[3]);
	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(camera.GetPosition());
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.7f, 2.f, 0.7f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);
	camera.SetClamp(Vector3(148, 400, 148));

	ui = new UI();
	ui->Init(Ayaka);
	ui->setCamera(&camera);

	{
		Environment[EN_FLOOR] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_LAND));
		//Environment[EN_FLOOR]->SetColliderBox(Vector3(150, 0.25, 150));
		Environment[EN_FLOOR]->SetScale(Vector3(300, 300, 300));
		Environment[EN_FLOOR]->SetRotate(Vector3(0, 180, 0));

		Environment[EN_HOUSE1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE1));
		Environment[EN_HOUSE1]->SetColliderBox(Vector3(12, 10, 9), Vector3(5, 1.6f, 0));
		Environment[EN_HOUSE1]->SetTranslate(Vector3(25, 8.6f, 10));
		//Environment[EN_HOUSE1]->SetTranslate(Vector3(25, 0.f, 10));
		Environment[EN_HOUSE1]->SetRotate(Vector3(0, -90, 0));

		Environment[EN_HOUSE2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE2));
		Environment[EN_HOUSE2]->SetColliderBox(Vector3(11, 9.5f, 12), Vector3(6.5f, 1, 1));
		Environment[EN_HOUSE2]->SetTranslate(Vector3(25, 8.6f, -30));
		Environment[EN_HOUSE2]->SetRotate(Vector3(0, 180, 0));

		Environment[EN_HOUSE3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE3));
		Environment[EN_HOUSE3]->SetColliderBox(Vector3(9, 8, 11), Vector3(-4, 1, 0));
		Environment[EN_HOUSE3]->SetTranslate(Vector3(-27, 7, 12));

		Environment[EN_HOUSE4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE1));
		Environment[EN_HOUSE4]->SetColliderBox(Vector3(12, 10, 9), Vector3(-4.4f, 1.6f, 0));
		Environment[EN_HOUSE4]->SetTranslate(Vector3(-27, 8.6, -30));
		Environment[EN_HOUSE4]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_HOUSE5] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE2));
		Environment[EN_HOUSE5]->SetColliderBox(Vector3(11, 9.5f, 11), Vector3(2, 1, -6));
		Environment[EN_HOUSE5]->SetTranslate(Vector3(-55, 8.6, 18));
		Environment[EN_HOUSE5]->SetRotate(Vector3(0, -90, 0));

		Environment[EN_STADIUM] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_STADIUM));
		Environment[EN_STADIUM]->SetColliderBox(Vector3(24, 8, 24), Vector3(0.8f, 1, 0));
		Environment[EN_STADIUM]->SetTranslate(Vector3(65, 7.5f, 100));
		Environment[EN_STADIUM]->SetRotate(Vector3(0, 90, 0));
		Environment[EN_STADIUM]->GetColliderBox(0)->setRotation(Environment[EN_STADIUM]->GetColliderBox(0)->GetRotation() + Vector3(0, 44, 0));

		Waypoints[WP_STADIUM] = new WayPoint("Stadium", Vector3(66.4f, 1, 65));
		Waypoints[WP_STADIUM]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
		Waypoints[WP_STADIUM]->SetRotate(Vector3(0, 180, 0));
		
		Environment[EN_GATE] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_GATE));
		Environment[EN_GATE]->SetColliderBox(Vector3(2, 19, 2), Vector3(-14.4f, 19, 0));
		Environment[EN_GATE]->SetColliderBox(Vector3(2, 19, 2), Vector3(14.4f, 19, 0));
		Environment[EN_GATE]->SetColliderBox(Vector3(2, 6, 28), Vector3(0, 37, 0));
		Environment[EN_GATE]->SetTranslate(Vector3(0, 0, -48));
		Environment[EN_GATE]->SetRotate(Vector3(0, 90, 0));
		Environment[EN_GATE]->SetScale(Vector3(8, 8, 8));

		Environment[EN_SCHOOL] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_SCHOOL));
		Environment[EN_SCHOOL]->SetColliderBox(Vector3(20, 13, 31), Vector3(-17, 13, 0));
		Environment[EN_SCHOOL]->SetColliderBox(Vector3(3, 13, 8), Vector3(6, 13, 0.5f));
		Environment[EN_SCHOOL]->SetTranslate(Vector3(-55, 0, -80));
		Environment[EN_SCHOOL]->SetScale(Vector3(1.4f, 1.4f, 1.4f));
		Waypoints[WP_LIBRARY] = new WayPoint("Library", Vector3(-44, 1, -80));
		Waypoints[WP_LIBRARY]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
		Waypoints[WP_LIBRARY]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_FANCYHOUSE] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_LIBRARY));
		Environment[EN_FANCYHOUSE]->SetColliderBox(Vector3(22, 10, 20), Vector3(4, 10, 0));
		Environment[EN_FANCYHOUSE]->SetTranslate(Vector3(55, 0, -80));
		Environment[EN_FANCYHOUSE]->SetRotate(Vector3(0, 90, 0));
		Waypoints[WP_TRAIN] = new WayPoint("Train Station", Vector3(35, 1, -80));
		Waypoints[WP_TRAIN]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
		Waypoints[WP_TRAIN]->SetRotate(Vector3(0, -90, 0));

		Environment[EN_PAGODA] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PAGODA));
		Environment[EN_PAGODA]->SetTranslate(Vector3(-100, -0.4f, 65));
		Environment[EN_PAGODA]->SetColliderBox(Vector3(29, 3, 29), Vector3(2, 2.4f, 0)); //Platform
		Environment[EN_PAGODA]->SetColliderBox(Vector3(15, 40, 15), Vector3(0, 40, 0)); //Pagoda
		Environment[EN_PAGODA]->SetColliderBox(Vector3(7, 3, 1), Vector3(31.6f, 1.4, 0)); //Stairs
		Environment[EN_PAGODA]->SetColliderBox(Vector3(7, 3, 1), Vector3(33.5f, 0, 0));
		Environment[EN_PAGODA]->SetColliderBox(Vector3(7, 3, 1), Vector3(35.5f, -1.4f, 0));
		Environment[EN_PAGODA]->SetRotate(Vector3(0, 90, 0));
		Waypoints[WP_HALL] = new WayPoint("Hall", Vector3(-84, 5, 65));
		Waypoints[WP_HALL]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));
		Waypoints[WP_HALL]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_TREE] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TREE));
		Environment[EN_TREE]->SetColliderBox(Vector3(1, 7, 1), Vector3(0, 7, 0));
		Environment[EN_TREE]->SetTranslate(Vector3(-20, 0, -10));
		Environment[EN_TREE]->SetScale(Vector3(10, 10, 10));
	}

	Boost = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FAN));
	Boost->SetTranslate(Vector3(25, 0, -60));
	Boost->SetScale(Vector3(0.6f, 0.6f, 0.6f));
	Boost->SetColliderBox(Vector3(2.5f, 50, 2.5f), Vector3(0, 26, 0));

	GenerateNPCs(meshlist);
}

void SceneCity::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_SUN]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 500, -150), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -80, 150));
}


void SceneCity::Update(double dt)
{
	if(!bPauseGame)
	{
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

			if (Application::IsKeyPressed('Z'))
			{
				Cube[1]->SetRotate(Cube[1]->GetRotate() + Vector3(0, SPEED * 10, 0));
			}
			if (Application::IsKeyPressed('X'))
			{
				Cube[1]->SetRotate(Cube[1]->GetRotate() + Vector3(0, -SPEED * 10, 0));
			}

			Cube[0]->SetTranslate(Cube[0]->GetTranslate() + Direction * SPEED);
			Cube[0]->UpdateChildCollision();
			//Vector3 temp1 = Cube[1]->GetColliderBox(0)->GetTranslate();
			//Vector3 temp2 = Cube[2]->GetColliderBox(0)->GetTranslate();
			//std::cout << temp1 << std::endl;
			//std::cout << temp2 << std::endl;
			//system("CLS");
		}

		//Movement Update
		camera.Updatemovement(dt);
		Ayaka->Update(dt);
		//Collision Update
		Ayaka->CollisionResolution(Cube[0]);
		Ayaka->CollisionResolution(Cube[1]);
		for (int i = 0; i < EN_TOTAL; i++)
		{
			if (Environment[i])
			{
				if (Environment[i]->GetCollVecSize() != 0)
					Ayaka->CollisionResolution(Environment[i]);
			}
		}

		Boost->SetRotate(Boost->GetRotate() + Vector3(0, 100 * dt, 0));
		if (Ayaka->GetColliderBox(0)->CheckOBBCollision(Boost->GetColliderBox(0)).Collided)
		{
			Ayaka->setVertVelocity(25);
		}
		
		Waypoints[WP_STADIUM]->inRangeResponse(Ayaka, SceneManager::SCENE_STADIUM);
		Waypoints[WP_LIBRARY]->inRangeResponse(Ayaka, SceneManager::SCENE_LIBRARY);
		Waypoints[WP_HALL]->inRangeResponse(Ayaka, SceneManager::SCENE_HALL);
		Waypoints[WP_TRAIN]->inRangeResponse(Ayaka, SceneManager::SCENE_TRAIN);

		//UI
		UpdateNPCs(dt);
		//Debug
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
	}
	camera.Updateposition(); //update position according to character pos
	ui->Update(dt);
}

void SceneCity::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());
	renderer->SetToProj();
	for (int i = 0; i < LIGHT_TOTAL; i++)
		renderer->SetLight(lights[i], camera.GetPosition());

	Axis->Draw(renderer, false);

	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}
		
	Ayaka->Draw(renderer, true);
	DrawNPCs();
	Cube[0]->Draw(renderer, false);
	//Cube[1]->Draw(renderer, false);
	for (int i = 0; i < EN_TOTAL; i++)
	{
		if(Environment[i])
			Environment[i]->Draw(renderer, true);
	}

	Boost->Draw(renderer, true);
	
	for (int i = 0; i < WP_TOTAL; i++)
	{
		if (Waypoints[i])
			Waypoints[i]->DrawLocName(renderer);
	}
	
	ui->Draw(renderer, true);
	
	for (int i = 0; i < WP_TOTAL; i++)
	{
		if(Waypoints[i])
			Waypoints[i]->Draw(renderer);
	}
}

void SceneCity::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneCity::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}

void SceneCity::GenerateNPCs(MeshList* meshlist)
{
	for (int i = 0; i < NPC_TOTAL; i++) {
		npc[i] = goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_NPC));
		npc[i]->Init(meshlist, Ayaka);
		npc[i]->SetColliderBox(Vector3(0.5,1,0.5), Vector3(0,2,0));
		//Individually set their translations separately
	}
	
	npc[TRAIN_BUSY1]->SetTranslate(Vector3(23, 0, 9.5));
	npc[TRAIN_BUSY1]->PushPathPoint(6, 0, 9.5);
	npc[TRAIN_BUSY1]->PushPathPoint(6, 0, -78);
	npc[TRAIN_BUSY1]->PushPathPoint(33, 0, -78);
	npc[TRAIN_BUSY1]->PushPathPoint(35, 1, -78);
	npc[TRAIN_BUSY1]->PushDespawnPoint(40, 1, -78);
	npc[TRAIN_BUSY1]->SetRespawnPos(23,0,9.5);

	npc[TRAIN_BUSY2]->SetTranslate(Vector3(36, 0, -88));
	npc[TRAIN_BUSY2]->PushPathPoint(35.5, 0, -88);
	npc[TRAIN_BUSY2]->PushDespawnPoint(35.5, 0, -100);
	npc[TRAIN_BUSY2]->SetRespawnPos(35.5, 0, -99);

	npc[LIBRARY_BUSY1]->SetTranslate(Vector3(-50, 0, 18));
	npc[LIBRARY_BUSY1]->PushPathPoint(-50,0,35);
	npc[LIBRARY_BUSY1]->PushPathPoint(-8,0,35);
	npc[LIBRARY_BUSY1]->PushPathPoint(-8,0,-80);
	npc[LIBRARY_BUSY1]->PushDespawnPoint(-50, 0, -80);
	npc[LIBRARY_BUSY1]->SetRespawnPos(-50, 0, 18);

	npc[LIBRARY_REST]->SetDefaultPos(Vector3(-49, 0, -88));
	npc[LIBRARY_REST]->SetDefaultDir(Vector3(0, 90, 0));

}

void SceneCity::UpdateNPCs(double dt)
{
	for (int i = 0; i < NPC_TOTAL; i++) {
		Ayaka->IsWithinRangeOf(npc[i]);

		npc[i]->CollisionResolution(Ayaka);
		npc[i]->Update(dt);
		
	}
}

void SceneCity::DrawNPCs()
{
	for (int i = 0; i < NPC_TOTAL; i++) {
		npc[i]->Draw(renderer, true);
	}
}
