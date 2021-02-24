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
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(40, 5, -40), Vector3(-1, 0, 1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);

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
	Environment[EN_FLOOR] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FLOOR));
	Environment[EN_FLOOR]->SetScale(Vector3(100, 100, 100));

	Waypoint = new WayPoint("City", Vector3(0, 1, 0));
	Waypoint->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));

	ui = new UI();
	ui->Init(Ayaka);
	ui->setCamera(&camera);

	//Text
	{
		textarr[TEXT_FPS] = new Text();
		textarr[TEXT_FPS]->SetMode(Text::STATIC_SCREENTEXT);
		textarr[TEXT_FPS]->SetTranslate(Vector3(0, 0, 0));

		textarr[TEXT_POSITION] = new Text();
		textarr[TEXT_POSITION]->SetMode(Text::STATIC_SCREENTEXT);
		textarr[TEXT_POSITION]->SetTranslate(Vector3(0, 68, 0));
	}
}

void SceneStadium::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 80, -150), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -80, 150));

}

void SceneStadium::Update(double dt)
{
	fps = 1.f / dt;

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
	camera.Updateposition();

	

	//Text STuff
	{
		std::stringstream FPS;
		FPS.precision(4);
		FPS << "FPS: " << fps;
		textarr[TEXT_FPS]->SetText(FPS.str());

		std::stringstream Pos;
		Pos << "Position: " << Ayaka->GetTranslate().x << ", " << Ayaka->GetTranslate().y << ", " << Ayaka->GetTranslate().z;
		textarr[TEXT_POSITION]->SetText(Pos.str());
	}

	//UI
	
	ui->Update();

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

	for (int i = 0; i < LIGHT_TOTAL; i++)
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

	Waypoint->Draw(renderer, false);

	for (int i = 0; i < TEXT_TOTAL; i++)
	{
		if(textarr[i])
			textarr[i]->Draw(renderer, false);
	}

	ui->Draw(renderer, true);
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
