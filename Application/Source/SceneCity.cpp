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
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 3, -40), Vector3(0, 0, -1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);
	texturelist = new TextureList();
	meshlist = new MeshList(texturelist);

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
	Ayaka->Init(Vector3(0, 50, 5), Vector3(0, 0, 0), Vector3(0.2f, 0.2f, 0.2f));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox(Vector3(0.8f, 2.f, 0.8f), Vector3(0, 2, 0));

	{
		Environment[EN_FLOOR] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FLOOR));
		//Environment[EN_FLOOR]->SetColliderBox(Vector3(150, 0.25, 150));
		Environment[EN_FLOOR]->SetScale(Vector3(300, 300, 300));
		Environment[EN_FLOOR]->SetRotate(Vector3(0, 180, 0));

		Environment[EN_HOUSE1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE1));
		//Environment[EN_HOUSE1]->SetTranslate(Vector3(25, 8.6f, 10));
		Environment[EN_HOUSE1]->SetTranslate(Vector3(25, 0.f, 10));
		Environment[EN_HOUSE1]->SetRotate(Vector3(0, -90, 0));
		Environment[EN_HOUSE1]->SetColliderBox(Vector3(9, 2, 12), Vector3(3.4f, 1.6f, 0));

		Environment[EN_HOUSE2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE2));
		Environment[EN_HOUSE2]->SetTranslate(Vector3(25, 8.6f, -30));
		Environment[EN_HOUSE2]->SetRotate(Vector3(0, 180, 0));
		Environment[EN_HOUSE2]->SetColliderBox(Vector3(10, 9.5f, 12), Vector3(6, 1, 1));
	
		Environment[EN_HOUSE3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE3));
		Environment[EN_HOUSE3]->SetTranslate(Vector3(-27, 7, 12));
		Environment[EN_HOUSE3]->SetColliderBox(Vector3(9, 8, 11), Vector3(-4, 1, 0));
	
		Environment[EN_HOUSE4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE1));
		Environment[EN_HOUSE4]->SetTranslate(Vector3(-27, 8.6, -11));
		Environment[EN_HOUSE4]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_HOUSE5] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE2));
		Environment[EN_HOUSE5]->SetTranslate(Vector3(-55, 8.6, 18));
		Environment[EN_HOUSE5]->SetRotate(Vector3(0, -90, 0));

		/*Environment[EN_HOUSE4]->SetTranslate(Vector3(-25, 8.6f, -35));
		Environment[EN_HOUSE4]->SetRotate(Vector3(0, 90, 0));
		Environment[EN_HOUSE4]->SetColliderBox(Vector3(9, 10, 12), Vector3(-3.4f, 1.6f, 0.2f));*/
		
		//Environment[EN_HOUSE5] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE5));
		//Environment[EN_HOUSE5]->SetTranslate(Vector3(-48, 6, 50));
		//Environment[EN_HOUSE5]->SetRotate(Vector3(0, -90, 0));

		//Environment[EN_TOWER1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_TOWER));
		//Environment[EN_TOWER1]->SetTranslate(Vector3(-15, 12, -20));
	}
}

void SceneCity::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 50, 80), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -50, -80));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_POINT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneCity::Update(double dt)
{
	//have something else update teh cam. to have access to both cam and character
	if (camera.GetMode() == CameraVer2::THIRD_PERSON)
		Ayaka->Update(&camera, dt);
	else
		camera.Updatemovement(dt);

	Collision::OBBResolution(Ayaka, Cube[0]);
	Collision::OBBResolution(Ayaka, Cube[1]);
	Collision::OBBResolution(Ayaka, Environment[EN_HOUSE1]);
	Collision::OBBResolution(Ayaka, Environment[EN_HOUSE2]);
	Collision::OBBResolution(Ayaka, Environment[EN_HOUSE3]);
	Collision::OBBResolution(Ayaka, Environment[EN_HOUSE4]);

	//Update Camera after updating collision
	if (camera.GetMode() == CameraVer2::THIRD_PERSON)
		camera.SetTarget(Ayaka->GetTranslate() + Vector3(0, 3.5f, 0));

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

		lights[1]->position += Direction * SPEED;
		Cube[0]->SetTranslate(lights[0]->position);
		Cube[1]->SetTranslate(lights[1]->position);
		//Collision::OBBResolution(Cube[0], Cube[1]);
	}
}

void SceneCity::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());

	for (int i = 0; i < 2; i++)
		renderer->SetLight(lights[i], camera.GetPosition());
	//renderer->SetLight(lights[1]);

	Axis->Draw(renderer, false);

	for (int i = 0; i < Skybox::SBX_TOTAL; i++)
	{
		skybox->GetSBX(i)->Draw(renderer, false);
	}
		
	Cube[0]->Draw(renderer, false);
	Cube[1]->Draw(renderer, false);
	Environment[EN_FLOOR]->Draw(renderer, true);
	Environment[EN_HOUSE1]->Draw(renderer, true);
	Environment[EN_HOUSE2]->Draw(renderer, true);
	Environment[EN_HOUSE3]->Draw(renderer, true);
	Environment[EN_HOUSE4]->Draw(renderer, true);
	Environment[EN_HOUSE5]->Draw(renderer, true);

	//Environment[EN_HOUSE5]->Draw(renderer, true);

	//Environment[EN_TOWER1]->Draw(renderer, true);

	Ayaka->Draw(renderer, true);
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
