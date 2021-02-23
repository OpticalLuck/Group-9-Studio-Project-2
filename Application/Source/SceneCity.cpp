#include "SceneCity.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"
#include "shader.hpp"

#include "SceneManager.h"

SceneCity::SceneCity() :
	fps(0.f)
{
}

SceneCity::~SceneCity()
{
}

void SceneCity::Init()
{
	isInit = true; 
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 5, -90), Vector3(0, 0, 1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);
	lights[1] = new Light(Shader::GetInstance()->shaderdata, 1);
	
	MeshList* meshlist = MeshList::GetInstance();

	skybox = new Skybox(goManager, meshlist, 3);

	MainChar = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_CUBE));
	MainChar->Init(Vector3(0, 3, -40));
	MainChar->SetTranslate(MainChar->GetTranslate() + Vector3(0,30,0));
	MainChar->SetColliderBox();
	//MainChar->SetCamera(&camera);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));
	Cube[0] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[0]->SetTranslate(Vector3(-20, 3, -15));
	Cube[0]->SetColliderBox();

	Cube[1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_CUBE));
	Cube[1]->SetTranslate(Vector3(0, 3, 0));
	Cube[1]->SetColliderBox(Vector3(0.5f, 0.5f, 0.5f), Vector3(5, 0, 0));
	Cube[1]->SetColliderBox(Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 0, 5));

	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(camera.GetPosition(), Vector3(0, 0, 0), Vector3(0.2f, 0.2f, 0.2f));
	Ayaka->SetRotate(Vector3(0,Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)) ,0));
	Ayaka->SetColliderBox( Vector3(0.3, 0.5, 0.3), Vector3(0,0.5,0) ); //foot box (always first)
	//Ayaka->SetColliderBox( Vector3(0.35, 0.49, 0.35), Vector3(0,0.5,0) ); 
	Ayaka->SetColliderBox(Vector3(0.7f, 2.f, 0.7f), Vector3(0, 2, 0));

	{
		Environment[EN_FLOOR] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_FLOOR));
		//Environment[EN_FLOOR]->SetColliderBox(Vector3(150, 0.25, 150));
		Environment[EN_FLOOR]->SetScale(Vector3(300, 300, 300));
		Environment[EN_FLOOR]->SetRotate(Vector3(0, 180, 0));

		Environment[EN_HOUSE1] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE1));
		Environment[EN_HOUSE1]->SetColliderBox(Vector3(9, 10, 12), Vector3(3.4f, 1.6f, 0));
		Environment[EN_HOUSE1]->SetTranslate(Vector3(25, 8.6f, 10));
		//Environment[EN_HOUSE1]->SetTranslate(Vector3(25, 0.f, 10));
		Environment[EN_HOUSE1]->SetRotate(Vector3(0, -90, 0));

		Environment[EN_HOUSE2] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE2));
		Environment[EN_HOUSE2]->SetColliderBox(Vector3(10, 9.5f, 12), Vector3(6, 1, 1));
		Environment[EN_HOUSE2]->SetTranslate(Vector3(25, 8.6f, -30));
		Environment[EN_HOUSE2]->SetRotate(Vector3(0, 180, 0));
	
		Environment[EN_HOUSE3] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE3));
		Environment[EN_HOUSE3]->SetColliderBox(Vector3(9, 8, 11), Vector3(-4, 1, 0));
		Environment[EN_HOUSE3]->SetTranslate(Vector3(-27, 7, 12));
	
		Environment[EN_HOUSE4] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE1));
		Environment[EN_HOUSE4]->SetColliderBox(Vector3(9, 10, 12), Vector3(-3.4f, 1.6f, 0));
		Environment[EN_HOUSE4]->SetTranslate(Vector3(-27, 8.6, -30));
		Environment[EN_HOUSE4]->SetRotate(Vector3(0, 90, 0));

		Environment[EN_HOUSE5] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_HOUSE2));
		Environment[EN_HOUSE5]->SetTranslate(Vector3(-55, 8.6, 18));
		Environment[EN_HOUSE5]->SetRotate(Vector3(0, -90, 0));
		
		Environment[EN_STADIUM] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_STADIUM));
		Environment[EN_STADIUM]->SetColliderBox(Vector3(24, 8, 24), Vector3(0.8f, 1, 0));
		Environment[EN_STADIUM]->SetTranslate(Vector3(65, 7.5f, 100));
		Environment[EN_STADIUM]->SetRotate(Vector3(0, 90, 0));
		Environment[EN_STADIUM]->GetColliderBox(0)->setRotation(Environment[EN_STADIUM]->GetColliderBox(0)->GetRotation() + Vector3(0, 44, 0));

		Waypoints[WP_STADIUM] = new WayPoint("Stadium", Vector3(66.4f, 1, 65));
		Waypoints[WP_STADIUM]->SetMesh(meshlist->GetMesh(MeshList::MESH_CUBE));

		Environment[EN_GATE] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_GATE));
		Environment[EN_GATE]->SetTranslate(Vector3(0, 0, -48));
		Environment[EN_GATE]->SetRotate(Vector3(0, 90, 0));
		Environment[EN_GATE]->SetScale(Vector3(8, 8, 8));

		Environment[EN_SCHOOL] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_SCHOOL));
		Environment[EN_SCHOOL]->SetTranslate(Vector3(-55, 0, -80));
		
		Environment[EN_LIBRARY] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_LIBRARY));
		Environment[EN_LIBRARY]->SetTranslate(Vector3(55, 0, -80));
		Environment[EN_LIBRARY]->SetRotate(Vector3(0, 90, 0));
		
		Environment[EN_PAGODA] = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_PAGODA));
		Environment[EN_PAGODA]->SetTranslate(Vector3(-100, -0.4f, 65));
		Environment[EN_PAGODA]->SetRotate(Vector3(0, 90, 0));

	}

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

void SceneCity::InitGL()
{
	renderer = new Renderer(LIGHT_TOTAL);
	lights[LIGHT_MIDDLE]->Set(Light::LIGHT_DIRECTIONAL, Vector3(0, 80, -150), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, -80, 150));
	//lights[0]->Set(Light::LIGHT_SPOT, Vector3(0, 5, 0), Color(1, 1, 1), 2.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
	lights[1]->Set(Light::LIGHT_POINT, Vector3(10, 5, 10), Color(1, 1, 1), 1.f, 1.f, 0.1f, 0.001f, Vector3(0, 1, 0));
}


void SceneCity::Update(double dt)
{
	fps = 1.f / dt;
	//have something else update teh cam. to have access to both cam and character
	if (camera.GetMode() == CameraVer2::THIRD_PERSON)
		Ayaka->Update(&camera, dt);
	else
		camera.Updatemovement(dt);

	//Collision
	Ayaka->CollisionResolution(Cube[0]);
	Ayaka->CollisionResolution(Cube[1]);
	for (int i = 0; i < EN_TOTAL; i++)
	{
		if (Environment[i])
		{
			if (Environment[i]->GetCollVecSize() != 0)
				Ayaka->CollisionResolution(Environment[i]);
		}
	}

	

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

	if (Application::IsKeyPressed('E'))
	{
		if (Waypoints[WP_STADIUM]->getisInRange()) //SWAPPING SCENE
		{
			SceneManager::ChangeScene(SceneManager::SCENE_NPCTEST);
		}
	}


	//Text STuff
	{
		//UI TEXT
		Waypoints[WP_STADIUM]->inRangeResponse(Ayaka);

		std::stringstream FPS;
		FPS.precision(4);
		FPS << "FPS: " << fps;
		textarr[TEXT_FPS]->SetText(FPS.str());

		std::stringstream Pos;
		Pos << "Position: " << Ayaka->GetTranslate().x << ", " << Ayaka->GetTranslate().y << ", " << Ayaka->GetTranslate().z;
		textarr[TEXT_POSITION]->SetText(Pos.str());
	}


	Vector3 Direction = Vector3(0, 0, 0);
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

	float SPEED = 5 * dt;
	Cube[0]->SetTranslate(Cube[0]->GetTranslate() + Direction * SPEED);
	lights[1]->position = Cube[0]->GetTranslate();
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
		
	Ayaka->Draw(renderer, true);
	Cube[0]->Draw(renderer, false);
	Cube[1]->Draw(renderer, false);

	for (int i = 0; i < EN_TOTAL; i++)
	{
		if(Environment[i])
			Environment[i]->Draw(renderer, true);
	}

	Waypoints[WP_STADIUM]->Draw(renderer, false);

	for (int i = 0; i < TEXT_TOTAL; i++)
	{
		textarr[i]->Draw(renderer, false);
	}
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
