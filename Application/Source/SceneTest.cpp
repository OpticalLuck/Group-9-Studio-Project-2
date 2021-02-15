#include "SceneTest.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"

SceneTest::SceneTest() :
	fps(0.f)
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
{
	renderer = new Renderer();
	//Init Meshlist
	meshlist = new MeshList();
	//Create Light
	lights[0] = new Light(renderer->GetprogramID(), 0);
	

	camera.Init(Vector3(0, 3, 8), Vector3(0, 0, -1), Vector3(0, 1, 0));

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Quad = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
	NPC =  goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_QUAD));

	text = new Text();
	text->SetMode(Text::STATIC_SCREENTEXT);
	text->SetText("Press F to Eject Pink Guy");
	text->SetTranslate(Vector3(-1.f, 4, 0));

	{
	lights[0]->Set(Light::LIGHT_POINT,
		           Vector3(0, 8, 0),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));
	}
}	

void SceneTest::Update(double dt)
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

	//LMB Click
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
}

void SceneTest::Render()
{
	renderer->Reset();

	//Camera
	renderer->SetCamera(camera);


	//Axis->Draw(renderer, false);
	//Quad->Draw(renderer, true);

	//Light
	renderer->SetLight(lights[0]);
	
	//Test TextonScreen
	text->Draw(renderer, false);
}

void SceneTest::Exit()
{
}

void SceneTest::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
