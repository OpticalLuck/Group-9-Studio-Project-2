#include "WayPoint.h"
#include "Application.h"
#include "MeshList.h"

WayPoint::WayPoint(std::string name, Vector3 position):
	isInRange(false),
	isEPressed(false)
{
	SetMesh(nullptr);
	SetTranslate(position);

	this->name = name;

	OnScreenText = new Text();
	OnScreenText->SetMode(Text::STATIC_SCREENTEXT);
	OnScreenText->SetText("Press E to go to " + name);
	OnScreenText->SetTranslate(Vector3(70, 72 * 0.5f, 0));
}

WayPoint::~WayPoint()
{
	delete OnScreenText;
}

void WayPoint::Draw(Renderer* renderer, bool enablelight)
{
	if (isInRange)
	{
		renderer->RenderTextOnScreen(OnScreenText->GetMesh(), OnScreenText->GetText(), Color(1, 1, 1), 4.f, OnScreenText->GetTranslate().x, OnScreenText->GetTranslate().y);
	}
}

void WayPoint::DrawLocName(Renderer* renderer)
{
	renderer->PushTransform();
	//scale, translate, rotate
	renderer->AddTransformation(GetTranslate(), GetRotate());
	if (getActive() && GetMesh())
	{
		renderer->RenderMesh(GetMesh(), false);
	}

	renderer->PushTransform();
	float textlength = name.length();
	renderer->AddTransformation(Vector3(textlength * -1, 8, 0), Vector3(0, 0, 0), Vector3(5, 5, 5));
	renderer->RenderText(MeshList::GetInstance()->GetMesh(MeshList::MESH_TEXT), name, Color(1, 1, 1));
	renderer->PopTransform();
	renderer->PopTransform();
}

bool WayPoint::inRangeResponse(GameObject* Target, SceneManager::SCENE_TYPE NextScene)
{
	if (GetInRange(Target, 2.f))
	{
		isInRange = true;
	}
	else
	{
		isInRange = false;
	}

	if (Application::IsKeyPressed('E') && isInRange && !isEPressed)
	{
		isEPressed = true;
		SceneManager::ChangeScene(NextScene);
	}
	else if (!Application::IsKeyPressed('E') && isEPressed)
	{
		isEPressed = false;
	}

	return isInRange;
}

std::string WayPoint::getLocation()
{
	return name;
}
