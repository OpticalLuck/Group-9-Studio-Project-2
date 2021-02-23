#include "SceneNPCTest.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

SceneNPCTest::SceneNPCTest() :
	fps(0.f)
{
}

SceneNPCTest::~SceneNPCTest()
{
}

void SceneNPCTest::Init()
{
	isInit = true;
	//Init Meshlist
	MeshList* meshlist = MeshList::GetInstance();
	//Create Light
	lights[0] = new Light(renderer->GetprogramID(), 0);
	
	camera.Init(Vector3(0, 3, 8), Vector3(0, 0, -1), Vector3(0, 1, 0));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Quad = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_QUAD));
	Quad->SetScale(Vector3(20, 20, 20));

	MainCharacter = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_CUBE));
	MainCharacter->SetColliderBox();
	MainCharacter->Init(Vector3(0, 3, 11));
	MainCharacter->SetRotate(Vector3(0, Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)), 0));

	npc =  goManager.CreateGO<NPC>(meshlist->GetMesh(MeshList::MESH_CUBE));
	npc->SetColliderBox();
	npc->Init(meshlist, MainCharacter, Vector3(0, 3, 0), Vector3(0, 90, 0));
	npc->PushPathPoint(Vector3(4, 3, 0));
	npc->PushPathPoint(Vector3(0, 3, -9));
	//npc->SetTranslate(Vector3(0,0,1));
}
void SceneNPCTest::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[0]->Set(Light::LIGHT_POINT,
				   Vector3(0, 8, 0),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));
}


void SceneNPCTest::Update(double dt)
{
	fps = 1.f / dt;
	static bool bLButtonState = false;

	if (camera.GetMode() == CameraVer2::THIRD_PERSON)
		MainCharacter->Update(&camera, dt);
	else
		camera.Updatemovement(dt);


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

	//LMB Click
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
	//MainCharacter->SetTranslate(camera.GetPosition());

	//MainCharacter->SetCamera(&camera);
	if (camera.GetMode() == CameraVer2::THIRD_PERSON)
		camera.SetTarget(MainCharacter->GetTranslate());
	MainCharacter->IsWithinRangeOf(npc);
	npc->Update(dt);

	//Collision::OBBResolution(npc, MainCharacter);
	//Collision::OBBResolution(MainCharacter, npc);
	
}

void SceneNPCTest::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	//Camera
	renderer->SetCamera(camera.GetPosition(), camera.GetView(), camera.GetUp());

	Axis->Draw(renderer, false);
	Quad->Draw(renderer, true);

	MainCharacter->Draw(renderer, false);
	npc->Draw(renderer, false);

	//Light
	renderer->SetLight(lights[0], camera.GetPosition());
	
}

void SceneNPCTest::Exit()
{
	delete renderer;
	Shader::Destroy();
}

void SceneNPCTest::UpdateMousePos(double xoffset, double yoffset)
{
	camera.Update(xoffset, yoffset);
}
