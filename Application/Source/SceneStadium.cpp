#include "SceneStadium.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "shader.hpp"
#include "SceneManager.h"
#include <sstream>

SceneStadium::SceneStadium()
{
}

SceneStadium::~SceneStadium()
{
}

void SceneStadium::Init()
{
	isInit = true;
	//camera.Init(Vector3(0, 5, -5), Vector3(0, 0, 1));
	camera.Init(Vector3(0, 5, -90), Vector3(0, 0, 1));
	camera.ToggleMode(CameraVer2::THIRD_PERSON);

	lights[0] = new Light(Shader::GetInstance()->shaderdata, 0);
	lights[1] = new Light(Shader::GetInstance()->shaderdata, 1);

	MeshList* meshlist = MeshList::GetInstance();

	skybox = new Skybox(goManager, meshlist, 3);

	Axis = goManager.CreateGO<GameObject>(meshlist->GetMesh(MeshList::MESH_AXIS));

	Ayaka = goManager.CreateGO<Character>(meshlist->GetMesh(MeshList::MESH_AYAKA));
	Ayaka->Init(camera.GetPosition(), Vector3(0, 0, 0), Vector3(0.2f, 0.2f, 0.2f));
	Ayaka->SetRotate(Vector3(0, Math::RadianToDegree(atan2(camera.GetView().x, camera.GetView().z)), 0));

	//Ayaka->SetColliderBox( Vector3(0.35, 0.49, 0.35), Vector3(0,0.5,0) ); 
	Ayaka->SetColliderBox(Vector3(0.7f, 2.f, 0.7f), Vector3(0, 2, 0));
	camera.SetTarget(Ayaka);

	ui = new UI();
	ui->Init(Ayaka);
}

void SceneStadium::InitGL()
{
}

void SceneStadium::Update(double dt)
{
}

void SceneStadium::Render()
{
}

void SceneStadium::Exit()
{
}

void SceneStadium::UpdateMousePos(double xoffset, double yoffset)
{
}
