#include "SceneStadium.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "shader.hpp"
#include "SceneManager.h"
#include <sstream>

SceneStadium::SceneStadium()
{
}

SceneStadium::~SceneStadium()
{
}

void SceneStadium::Init()
{
	isInit = true;
	RingCollected = 0;
	maxRing = 16;
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(-40, 5, 40), Vector3(1, 0, -1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	for (int i = 0; i < 4; i++)
	{
		lights[i] = new Light(Shader::GetInstance()->shaderdata, i);
	}

	MeshList* meshlist = MeshList::GetInstance();

	skybox = new Skybox(goManager, meshlist, 3);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));

	//Character
	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(camera.GetPosition());
	Ayaka->SetRotate(Vector3(0, Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)), 0));
	Ayaka->SetColliderBox(Vector3(0.7f, 2.f, 0.7f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);

	//Surroundings
	Environment[EN_FLOOR] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FIELD));
	Environment[EN_FLOOR]->SetScale(Vector3(100, 100, 100));

	Boost[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FAN));
	Boost[0]->SetTranslate(Vector3(-30, 0, 30));
	Boost[0]->SetScale(Vector3(0.6f, 0.6f, 0.6f));
	Boost[0]->SetColliderBox(Vector3(2.5f, 50, 2.5f), Vector3(0,26,0));

	Boost[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FAN));
	Boost[1]->SetTranslate(Vector3(30, 0, -30));
	Boost[1]->SetScale(Vector3(0.6f, 0.6f, 0.6f));
	Boost[1]->SetColliderBox(Vector3(2.5f, 50, 2.5f), Vector3(0, 26, 0));

	Waypoint = new WayPoint("City", Vector3(-45, 1, 45));
	Waypoint->SetRotate(Vector3(0, 135, 0));
	Waypoint->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));

	Math::InitRNG();
	for (int i = 0; i < maxRing; i++)
	{
		Rings[i] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_RING));
		bool setCoord = false;

		while (!setCoord)
		{
			Vector3 CoordRand = Vector3(Math::RandFloatMinMax(-40, 40),
										Math::RandFloatMinMax(10, 80),
										Math::RandFloatMinMax(-40, 40));
			float RotateRand = Math::RandFloatMinMax(0, 360);

			//Set initial ring
			Rings[i]->SetTranslate(CoordRand);
			Rings[i]->SetRotate(Vector3(0, RotateRand, 0));
			Rings[i]->SetColliderBox(Vector3(6, 6, 1));

			for (int j = 0; j < maxRing; j++) // Check for collision in randomization
			{
				if (Rings[j] && i != j)
				{
					if (Rings[i]->GetColliderBox(0)->CheckOBBCollision(Rings[j]->GetColliderBox(0)).Collided) //collision detected
					{
						CoordRand = Vector3(Math::RandFloatMinMax(-40, 40),
							Math::RandFloatMinMax(10, 80),
							Math::RandFloatMinMax(-40, 40));
						RotateRand = Math::RandFloatMinMax(0, 360);
						Rings[i]->SetTranslate(CoordRand);
						Rings[i]->SetRotate(Vector3(0, RotateRand, 0));
					}
					else
					{
						setCoord = true;
					}
				}
				if (j == maxRing - 1) //Check coll done
				{
					setCoord = true;
					std::cout << "END LOOP" << std::endl;
				}
			}
		}
	}

	ui = new UI();
	ui->Init(Ayaka);
	ui->setCamera(&camera);

	//Text
	{
		instructions = new Text();
		instructions->SetMode(Text::STATIC_SCREENTEXT);
		instructions->SetTranslate(Vector3(32, 64, 0));
	}

}

void SceneStadium::InitGL()
{
	renderer = new Renderer(4);
	lights[0]->Set(Light::LIGHT_DIRECTIONAL, Vector3(50, 150, 50), Color(1, 1, 1), 0.5f, 1.f, 0.1f, 0.001f, Vector3(-50, -1, -50));
	lights[1]->Set(Light::LIGHT_DIRECTIONAL, Vector3(50, 150, -50), Color(1, 1, 1), 0.5f, 1.f, 0.1f, 0.001f, Vector3(-50, -1, 50));
	lights[2]->Set(Light::LIGHT_DIRECTIONAL, Vector3(-50, 150, -50), Color(1, 1, 1), 0.5f, 1.f, 0.1f, 0.001f, Vector3(50, -1, 50));
	lights[3]->Set(Light::LIGHT_DIRECTIONAL, Vector3(-50, 150, 50), Color(1, 1, 1), 0.5f, 1.f, 0.1f, 0.001f, Vector3(50, -1, -50));
}

void SceneStadium::Update(double dt)
{
	fps = 1.f / dt;

	Ayaka->setRingCount(RingCollected);

	//Movement Update
	camera.Updatemovement(dt);
	Ayaka->Update(dt);
	//Collision Update
	for (int i = 0; i < EN_TOTAL; i++)
	{
		if (Environment[i])
		{
			if (Environment[i]->GetCollVecSize() != 0)
				Ayaka->CollisionResolution(Environment[i]);
		}
	}

	//Game Logic
	{
		//Fan
		if (Ayaka->GetColliderBox(0)->CheckOBBCollision(Boost[0]->GetColliderBox(0)).Collided || Ayaka->GetColliderBox(1)->CheckOBBCollision(Boost[1]->GetColliderBox(0)).Collided)
		{
			Ayaka->setVertVelocity(25);
		}

		//Ring
		for (int i = 0; i < maxRing; i++)
		{
			if (Ayaka->GetColliderBox(1)->CheckOBBCollision(Rings[i]->GetColliderBox(0)).Collided && Rings[i]->getActive())
			{
				Rings[i]->SetActive(false);
				RingCollected++;
			}

			if (RingCollected == maxRing)
			{
				setQuestStatus(true);
			}
		}

		//if feet touch ground - reset
		if (Ayaka->getbGrounded() && RingCollected != maxRing)
		{
			RingCollected = 0;
			for (int i = 0; i < maxRing; i++)
			{
				Rings[i]->SetActive(true);
			}
		}
	}
	
	camera.Updateposition();
	
	Boost[0]->SetRotate(Boost[0]->GetRotate() + Vector3(0, 100 * dt, 0));
	Boost[1]->SetRotate(Boost[1]->GetRotate() + Vector3(0, 100 * dt, 0));

	//Text STuff
	{
		std::stringstream ss;
		ss.precision(4);
		ss << "Collect All 16 Rings without touching the floor. " << RingCollected << "/" << maxRing;
		instructions->SetText(ss.str());
	}

	//UI
	
	ui->Update(dt);

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
	Waypoint->inRangeResponse(Ayaka, SceneManager::SCENE_CITY); //SWAPPING SCENE

}

void SceneStadium::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());
	renderer->SetToProj();

	for (int i = 0; i < 4; i++)
		renderer->SetLight(lights[i], camera.GetPosition());

	Axis->Draw(renderer, false);

	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}

	Ayaka->Draw(renderer, true);

	for (int i = 0; i < EN_TOTAL; i++)
	{
		if (Environment[i])
			Environment[i]->Draw(renderer, true);
	}

	Boost[0]->Draw(renderer, true);
	Boost[1]->Draw(renderer, true);


	for (int i = 0; i < maxRing; i++)
	{
		Rings[i]->Draw(renderer, true);
	}

	Waypoint->DrawLocName(renderer);
	instructions->Draw(renderer, false);
	ui->Draw(renderer, true);
	Waypoint->Draw(renderer, false);

}

void SceneStadium::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneStadium::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}

int SceneStadium::getRingCount()
{
	return RingCollected;
}