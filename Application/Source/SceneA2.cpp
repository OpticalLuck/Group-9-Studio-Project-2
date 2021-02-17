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
	//Init Meshlist
	meshlist = new MeshList();
	//Create Light
	lights[0] = new Light(renderer->GetprogramID(), 0);

	camera.Init(Vector3(0, 3, -8), Vector3(0, 0, 1), Vector3(0, 1, 0));

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));

	Cube[0] = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[0]->Init(Vector3(5, 0, 5), Vector3(0, 0, 0), Vector3(1,1,1), Vector3(1,1,1));

	Cube[1] = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[1]->Init();

	NPC =  goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_QUAD));

	{
	lights[0]->Set(Light::LIGHT_POINT,
		           Vector3(0, 8, 0),
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

	//LMB Click
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}

	{
		float speed = 5 * dt;
		Vector3 direction = Vector3(0, 0, 0);

		if(Application::IsKeyPressed('I'))
		{
			direction = direction + Vector3(0, 0, 1);
		}
		if(Application::IsKeyPressed('K'))
		{
			direction = direction + Vector3(0, 0, -1);
		}
		if(Application::IsKeyPressed('J'))
		{
			direction = direction + Vector3(1, 0, 0);
		}
		if(Application::IsKeyPressed('L'))
		{
			direction = direction + Vector3(-1, 0, 0);
		}
		if (Application::IsKeyPressed('U'))
		{
			direction = direction + Vector3(0, 1, 0);
		}
		if (Application::IsKeyPressed('O'))
		{
			direction = direction + Vector3(0, -1, 0);
		}

		if (Application::IsKeyPressed('T'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(speed * 10, 0, 0));
		}
		if (Application::IsKeyPressed('G'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(-speed * 10, 0, 0));

		}
		if (Application::IsKeyPressed('F'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, 0, -speed * 10));
		}
		if (Application::IsKeyPressed('H'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, 0, speed * 10));

		}
		if (Application::IsKeyPressed('R'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, speed * 10, 0));
		}
		if (Application::IsKeyPressed('Y'))
		{
			Cube[0]->SetRotate(Cube[0]->GetRotate() + Vector3(0, -speed * 10, 0));
		}
		Cube[0]->SetTranslate(Vector3(Cube[0]->GetTranslate()) + speed * direction);
		Cube[0]->Update(dt);
		
		//OBB RESOLUTION
		Info isCollided = Collision::CheckOBBCollision(Cube[0]->GetCollBox(), Cube[1]->GetCollBox());

		if (isCollided.Collided)
		{
			Vector3 Movement = Vector3(0, 0, 0);
			Vector3 Distance = Cube[0]->GetCollBox()->GetPos() - Cube[1]->GetCollBox()->GetPos();
			float magnitude = (Distance).Dot(isCollided.Axis);
			Movement += magnitude * isCollided.Axis;
			//move position back until side just touch
			Cube[0]->SetTranslate(Cube[0]->GetTranslate() + Movement);
			Cube[0]->Update(dt);
		}
	}
}

void SceneA2::Render()
{
	renderer->Reset();

	//Camera
	renderer->SetCamera(camera);


	Axis->Draw(renderer, false);

	//Cube[0]->Draw(renderer, false);
	Cube[0]->GetCollBox()->DrawFrame(renderer);
	
	Cube[1]->Draw(renderer, false);
	//Light
	renderer->SetLight(lights[0]);
	
}

void SceneA2::Exit()
{
}

void SceneA2::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
