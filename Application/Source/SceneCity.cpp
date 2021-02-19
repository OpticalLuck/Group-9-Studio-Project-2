#include "SceneCity.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

SceneCity::SceneCity() :
	fps(0.f)
{
}

SceneCity::~SceneCity()
{
}

void SceneCity::Init()
{
	renderer = new Renderer(LIGHT_TOTAL);
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 3, -40), Vector3(0, 0, 1));
	camera.ToggleMode(CameraVer2::FREE_VIEW);
	meshlist = new MeshList();
	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);
	lights[1] = new Light(Shader::GetInstance()->shaderdata, 1);

	skybox = new Skybox(goManager, meshlist, 3);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Cube[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[0]->SetColliderBox();
	Cube[0]->SetTranslate(Vector3(5, 5, 0));

	Cube[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[1]->SetColliderBox(Vector3(2,2,2));
	Cube[1]->SetTranslate(Vector3(0,5,0));

	Environment[EN_FLOOR] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FLOOR));
	Environment[EN_FLOOR]->SetScale(Vector3(150, 150, 150));
	Environment[EN_FLOOR]->SetRotate(Vector3(0, 180, 0));

	Environment[EN_HOUSE1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE1));
	Environment[EN_HOUSE1]->SetTranslate(Vector3(15, 6, 0));

	Environment[EN_HOUSE2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE2));
	Environment[EN_HOUSE2]->SetTranslate(Vector3(15, 6, -20));
	Environment[EN_HOUSE2]->SetRotate(Vector3(0, 180, 0));
	
	Environment[EN_HOUSE3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE3));
	Environment[EN_HOUSE3]->SetTranslate(Vector3(-18, 4, 2));
	Environment[EN_HOUSE3]->SetRotate(Vector3(0, 95.5, 0));
	
	Environment[EN_TOWER1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TOWER));
	Environment[EN_TOWER1]->SetTranslate(Vector3(-15, 12, -20));

}

void SceneCity::InitGL()
{
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_SPOT, Vector3(0, 150, 0), Color(1, 1, 1), 50.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_SPOT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneCity::Update(double dt)
{
	camera.Updatemovement(dt);
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
	}
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
	Collision::OBBResolution(Cube[0], Cube[1]);
	
		
}

void SceneCity::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(camera);

	for (int i = 0; i < 2; i++)
		renderer->SetLight(lights[i], camera);
	//renderer->SetLight(lights[1]);

	Axis->Draw(renderer, false);

	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}
		
	Cube[0]->GetColliderBox()->DrawFrame(renderer);
	Cube[1]->Draw(renderer, false);
	Cube[1]->GetColliderBox()->DrawFrame(renderer);
	Environment[EN_FLOOR]->Draw(renderer, true);
	Environment[EN_HOUSE1]->Draw(renderer, true);
	Environment[EN_HOUSE2]->Draw(renderer, true);
	Environment[EN_HOUSE3]->Draw(renderer, true);
	Environment[EN_TOWER1]->Draw(renderer, true);
}

void SceneCity::Exit()
{
	Shader::Destroy();
}

void SceneCity::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
