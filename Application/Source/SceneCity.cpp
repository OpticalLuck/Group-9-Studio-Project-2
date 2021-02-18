#include "SceneCity.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"

SceneCity::SceneCity() :
	fps(0.f)
{
}

SceneCity::~SceneCity()
{
}

void SceneCity::Init()
{
	renderer = new Renderer();
	camera.Init(Vector3(0, 3, -40), Vector3(0, 0, 1));
	meshlist = new MeshList();
	lights[0] = new Light(renderer->GetprogramID(), 0);	
	lights[1] = new Light(renderer->GetprogramID(), 1);	

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Cube[1] = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Environment[EN_FLOOR] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FLOOR));
	Environment[EN_FLOOR]->SetScale(Vector3(150, 150, 150));
	Environment[EN_FLOOR]->SetRotate(Vector3(0, 180, 0));

	lights[0]->Set(Light::LIGHT_POINT, Vector3(0, 50, 0), Color(1, 1, 1), 20.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_SPOT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}	

void SceneCity::Update(double dt)
{
	Cube[1]->SetTranslate(lights[0]->position);

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
	float LSPEED = 5.f;
	if (Application::IsKeyPressed('I'))
		lights[0]->position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		lights[0]->position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		lights[0]->position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		lights[0]->position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		lights[0]->position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		lights[0]->position.y += (float)(LSPEED * dt);

}

void SceneCity::Render()
{
	renderer->Reset();
	//renderer->SetLight(lights[1]);
	renderer->LoadIdentity();
	renderer->SetCamera(camera);

	renderer->SetLight(lights[0], camera);

	Axis->Draw(renderer, false);
	Cube[1]->Draw(renderer, false);
	Environment[EN_FLOOR]->Draw(renderer, true);
}

void SceneCity::Exit()
{
}

void SceneCity::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
