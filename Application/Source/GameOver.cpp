#include "GameOver.h"
#include "MeshBuilder.h"
#include "Application.h"
#include "LoadTGA.h"
GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	isInit = true;
	isMousePressed = false;

	//float VertAlign = 25;
	float VertAlign = 64;
	MenuBtn[BTN_QUIT] = new Button(VertAlign, 36, 4, 1, 10);
	MenuBtn[BTN_QUIT]->SetTexture("Buttons/QuitBtn.tga");

	Background = MeshBuilder::GenerateQuad("End", Color(1, 1, 1), 128, 72);
	Background->textureArr[0] = LoadTGA("Image//EndBG.tga");

	TheEnd = MeshBuilder::GenerateQuad("End", Color(0, 1, 0), 80, 20);
	TheEnd->textureArr[0] = LoadTGA("Image//TheEnd.tga");
}

void GameOver::InitGL()
{
	renderer = new Renderer(0);
	Application::EnableCursor();
}

void GameOver::Update(double dt)
{
	double xpos, ypos;
	Application::GetCursorPos(&xpos, &ypos);

	if (MenuBtn[BTN_QUIT]->ScaleOnHover(xpos, ypos, 1.2) && Application::IsMousePressed(0) && !isMousePressed)
	{
		isMousePressed = true;
		MenuBtn[BTN_QUIT]->SetbClicked(true);
	}

	if (isMousePressed && !Application::IsMousePressed(0))
	{
		if (MenuBtn[BTN_QUIT]->isHoveredOn(xpos, ypos) && MenuBtn[BTN_QUIT]->getbClicked())
		{
			Application::bQuit = true;
		}
		else
		{
			isMousePressed = false;
			MenuBtn[BTN_QUIT]->SetbClicked(false);
		}
	}
}

void GameOver::Render()
{
	renderer->RenderMeshOnScreen(Background, 64, 36, 1, 1);
	renderer->RenderMeshOnScreen(TheEnd, 64, 55, 0.8f, 0.8f);
	MenuBtn[BTN_QUIT]->Draw(renderer);
}

void GameOver::Exit()
{
}

void GameOver::UpdateMousePos(double xoffset, double yoffset)
{
}
