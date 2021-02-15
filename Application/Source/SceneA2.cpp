#include "SceneA2.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"

SceneA2::SceneA2() :
	fps(0.f)
{
}

SceneA2::~SceneA2()
{
}

void SceneA2::Init()
{
	renderer = new Renderer();

	Axis = new GameObject(MeshBuilder::GenerateAxes("Axes", 1000, 1000, 1000));
	for (int i = 0; i < 4; i++)
	{
		lights[i] = new Light(renderer->GetprogramID(), i);
	}

	//meshlist
	meshlist = new MeshList();

	camera.Init(Vector3(0, 3, 8), Vector3(0, 0, -1), Vector3(0, 1, 0));
	//Set target as control character
	//camera.SetTarget();

	{
	lights[0]->Set(Light::LIGHT_POINT,
		           Vector3(10, 9, -10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));

	lights[1]->Set(Light::LIGHT_POINT,
				   Vector3(10, 9, 10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));

	lights[2]->Set(Light::LIGHT_POINT,
				   Vector3(-10, 9, -10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));

	lights[3]->Set(Light::LIGHT_POINT,
				   Vector3(-10, 9, 10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));
	}
}	

void SceneA2::Update(double dt)
{
	fps = 1.f / dt;
	static bool bLButtonState = false;
	//Debug controls
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
		//Input
		if (Application::IsKeyPressed('9'))
		{
			Application::EnableCursor();
		}
		if (Application::IsKeyPressed('0'))
		{
			Application::DisableCursor();
		}
	}

	camera.Updatemovement(dt);

	if (Application::IsKeyPressed('F'))
	{
	}
	//Button Click
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
	else if (Application::IsMousePressed(0))
	{
	}
	else
	{
	}
}

void SceneA2::Render()
{

	renderer->Reset();

	//Camera
	renderer->SetCamera(camera);
	Axis->Draw(renderer, false);

	//Light
	for (int i = 0; i < 4; i++) 
	{
		renderer->SetLight(lights[i]);
	}
}

void SceneA2::Exit()
{

}

void SceneA2::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
