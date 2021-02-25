#include "WayPoint.h"
#include "Application.h"

WayPoint::WayPoint(std::string name, Vector3 position):
	isInRange(false),
	isEPressed(false)
{
	SetMesh(nullptr);
	SetTranslate(position);

	OnScreenText = new Text();
	OnScreenText->SetMode(Text::STATIC_SCREENTEXT);
	OnScreenText->SetText("Press E to go " + name);
	OnScreenText->SetTranslate(Vector3(128 * 0.5f, 72 * 0.5f, 0));
}

WayPoint::~WayPoint()
{
	delete OnScreenText;
}

void WayPoint::Draw(Renderer* renderer, bool enablelight)
{
	renderer->PushTransform();
	//scale, translate, rotate
	renderer->AddTransformation(GetTranslate());
	if (getActive() && GetMesh())
	{
		renderer->RenderMesh(GetMesh(), enablelight);
	}
	if (isInRange)
	{
		renderer->RenderTextOnScreen(OnScreenText->GetMesh(), OnScreenText->GetText(), Color(0, 1, 0), 4.f, OnScreenText->GetTranslate().x, OnScreenText->GetTranslate().y);
	}
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
