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

		Collision* object = Cube[0]->GetCollBox();
		Collision* target = Cube[1]->GetCollBox();
		////X plane
		//float XDiff = Collision::getDiffX(object, target);
		////Y plane
		//float YDiff = Collision::getDiffY(object, target);
		////Z plane
		//float ZDiff = Collision::getDiffZ(object, target);
		//AABB RESOLUTION
		//if (Collision::CheckAABBCollision(Cube[0]->GetCollBox(), Cube[1]->GetCollBox()))
		//{
		//	Vector3 Movement = Vector3(0, 0, 0);
		//	if (abs(XDiff) < abs(ZDiff) && abs(XDiff) < abs(YDiff))
		//	{
		//		Movement += Vector3(XDiff, 0, 0);
		//	}
		//	if (abs(YDiff) < abs(XDiff) && abs(YDiff) < abs(ZDiff))
		//	{
		//		Movement += Vector3(0, YDiff, 0);
		//	}
		//	if (abs(ZDiff) < abs(XDiff) && abs(ZDiff) < abs(YDiff))
		//	{
		//		Movement += Vector3(0, 0, ZDiff);
		//	}
		//	//move position back until side just touch
		//	Cube[0]->SetTranslate(Cube[0]->GetTranslate() + Movement);
		//	Cube[0]->Update(dt);
		//}
		
		//OBB RESOLUTION
		
		if (Collision::CheckOBBCollision(Cube[0]->GetCollBox(), Cube[1]->GetCollBox()))
		{
			Vector3 Movement = Vector3(0, 0, 0);
			Vector3 aupdiff = Collision::getDiff(object->GetUp(), object, target);
			Vector3 bupdiff = Collision::getDiff(target->GetUp(), object, target);
			Vector3 afrontdiff = Collision::getDiff(object->GetFront(), object, target);
			Vector3 bfrontdiff = Collision::getDiff(target->GetFront(), object, target);
			Vector3 arightdiff = Collision::getDiff(object->GetRight(), object, target);
			Vector3 brightdiff = Collision::getDiff(target->GetRight(), object, target);
			
			Vector3 cross1dif = Collision::getDiff(object->GetUp().Cross(target->GetUp()), object, target);
			Vector3 cross2dif = Collision::getDiff(object->GetUp().Cross(target->GetRight()), object, target);
			Vector3 cross3dif = Collision::getDiff(object->GetUp().Cross(target->GetFront()), object, target);
			
			if (fabs(afrontdiff.Length()) < fabs(aupdiff.Length()) &&
				fabs(afrontdiff.Length()) < fabs(bupdiff.Length()) &&
				fabs(afrontdiff.Length()) < fabs(arightdiff.Length()) &&
				fabs(afrontdiff.Length()) < fabs(brightdiff.Length()) &&
				fabs(afrontdiff.Length()) < fabs(bfrontdiff.Length()))
			{
				Movement += afrontdiff;
			}
			if (fabs(bfrontdiff.Length()) < fabs(aupdiff.Length()) &&
				fabs(bfrontdiff.Length()) < fabs(bupdiff.Length()) &&
				fabs(bfrontdiff.Length()) < fabs(arightdiff.Length()) &&
				fabs(bfrontdiff.Length()) < fabs(brightdiff.Length()) &&
				fabs(bfrontdiff.Length()) < fabs(afrontdiff.Length()))
			{
				Movement += bfrontdiff;
			}

			if (fabs(arightdiff.Length()) < fabs(aupdiff.Length()) &&
				fabs(arightdiff.Length()) < fabs(bupdiff.Length()) &&
				fabs(arightdiff.Length()) < fabs(brightdiff.Length()) &&
				fabs(arightdiff.Length()) < fabs(afrontdiff.Length()) &&
				fabs(arightdiff.Length()) < fabs(bfrontdiff.Length()))
			{
				Movement += arightdiff;
			}
			if (fabs(brightdiff.Length()) < fabs(aupdiff.Length()) &&
				fabs(brightdiff.Length()) < fabs(bupdiff.Length()) &&
				fabs(brightdiff.Length()) < fabs(arightdiff.Length()) &&
				fabs(brightdiff.Length()) < fabs(bfrontdiff.Length()) &&
				fabs(brightdiff.Length()) < fabs(afrontdiff.Length()))
			{
				Movement += brightdiff;
			}


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
