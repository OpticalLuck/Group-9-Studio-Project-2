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
	x_width = 30;
	mapOpen = false;

	renderer = new Renderer();
	//Init Meshlist
	meshlist = new MeshList();
	//Create Light
	lights[0] = new Light(renderer->GetprogramID(), 0);
	

	camera.Init(Vector3(0, 3, 8), Vector3(0, 0, -1), Vector3(0, 1, 0));

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Quad = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
	Quad->SetScale(Vector3(20, 20, 20));

	Item[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Item[0]->SetTranslate(Vector3(3, 3, 0));
	
	Item[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Item[1]->SetTranslate(Vector3(-6, 3, 2));

	character =  goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_QUAD));

	text[0] = new Text();
	text[0]->SetMode(Text::STATIC_SCREENTEXT);
	text[0]->SetText("Press F to Eject Pink Guy");
	text[0]->SetTranslate(Vector3(-1.f, 4, 0));	
	
	text[1] = new Text();
	text[1]->SetMode(Text::STATIC_SCREENTEXT);
	text[1]->SetText("Walking");
	text[1]->SetTranslate(Vector3(-1.f, 4, 0));	
	
	text[2] = new Text();
	text[2]->SetMode(Text::STATIC_SCREENTEXT);
	text[2]->SetText("Sprinting");
	text[2]->SetTranslate(Vector3(-1.f, 4, 0));
	
	
	text[3] = new Text();
	text[3]->SetMode(Text::STATIC_SCREENTEXT);
	text[3]->SetText("Press E to Interact");
	text[3]->SetTranslate(Vector3(27.5, 12.5, 0));

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

		if (Application::IsKeyPressed('M'))
		{
			mapOpen = !mapOpen;
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


	camera.SetSprintState(false);
	if (Application::IsKeyPressed(VK_SHIFT) && (Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D')))
	{
		//using stamina bar
		if (x_width >= 0)
		{
			camera.SetSprintState(true);
			x_width -= 0.3;
		}
	}
	else
	{
		//recharging stamina bar
		if (x_width <= 30)
		{
			x_width += 0.3;
		}
	}

	character->SetTranslate(camera.GetPosition());
}

void SceneTest::Render()
{
	renderer->Reset();

	//Camera
	renderer->SetCamera(camera);


	Axis->Draw(renderer, false);
	Quad->Draw(renderer, true);

	for (int i = 0; i < sizeof(Item) / sizeof(Item[0]); i++)
	{
		Item[i]->Draw(renderer, true);

		if (character->IsWithinRangeOf(Item[i]))
		{
			text[3]->Draw(renderer, true);
		}
	}

	if (mapOpen == false)
	{
		renderer->RenderMeshOnScreen(meshlist->GetMesh(MeshList::MESH_STAMINABAR), 40, 10, x_width, 1);
	}
	else
	{
		renderer->RenderMeshOnScreen(meshlist->GetMesh(MeshList::MESH_QUAD), 40, 30, 50, 50);
		renderer->RenderMeshOnScreen(meshlist->GetMesh(MeshList::MESH_ICON), 40 + camera.GetPosX(), 30 - camera.GetPosZ(), 1, 1);
	}

	//Light
	renderer->SetLight(lights[0]);
	
	//Test TextonScreen
	//text[0]->Draw(renderer, false);

	//text to check if player is sprinting or walking
	if (camera.GetSprintState() == false)
	{
		text[1]->Draw(renderer, false);
	}
	else
	{
		text[2]->Draw(renderer, false);
	}
}

void SceneTest::Exit()
{
}

void SceneTest::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
