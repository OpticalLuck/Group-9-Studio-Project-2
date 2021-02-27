#include "MainMenu.h"
#include "shader.hpp"
#include "SceneManager.h"
#include "MeshBuilder.h"
#include "Application.h"
#include "LoadTGA.h"
MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
	if (SceneManager::getCurrentSceneType() == SceneManager::SCENE_MAINMENU)
	{
		delete renderer;
	}
	delete BackGround;
	delete Logo;
	//Delete Buttons
	for (int i = 0; i < BTN_TOTAL; i++)
	{
		delete MenuBtn[i];
	}
}

void MainMenu::Init()
{
	isInit = true;
	isMousePressed = false;
	float VertAlign = 25;
	MenuBtn[BTN_START] = new Button(VertAlign, 40, 4, 1, 10);
	MenuBtn[BTN_START]->SetTexture("Buttons/PlayBtnArrow.tga");
	MenuBtn[BTN_CONTROLS] = new Button(VertAlign, 25, 4, 1, 10);
	MenuBtn[BTN_CONTROLS]->SetTexture("Buttons/ControlsBtnArrow.tga");
	MenuBtn[BTN_QUIT] = new Button(VertAlign, 10, 4, 1, 10);
	MenuBtn[BTN_QUIT]->SetTexture("Buttons/QuitBtnArrow.tga");

	BackGround = MeshBuilder::GenerateQuad("Background", Color(1, 1, 1), 128, 72);
	BackGround->textureArr[0] = LoadTGA("Image//MainMenu.tga");
	Logo = MeshBuilder::GenerateQuad("Logo", Color(1, 1, 1), 60, 18);
}

void MainMenu::InitGL()
{
	renderer = new Renderer(0);
}

void MainMenu::Update(double dt)
{
	//Application::DisableCursor(); //Disable Cursor when going into scene
	double xpos, ypos;
	Application::GetCursorPos(&xpos, &ypos);
	if (MenuBtn[BTN_START]->SlideOnHover(xpos, ypos, 3.5f) && Application::IsMousePressed(0) && !isMousePressed)
	{
		isMousePressed = true;
		MenuBtn[BTN_START]->SetbClicked(true);
	}
	if (MenuBtn[BTN_CONTROLS]->SlideOnHover(xpos, ypos, 3.5f) && Application::IsMousePressed(0) && !isMousePressed)
	{
		isMousePressed = true;
		MenuBtn[BTN_CONTROLS]->SetbClicked(true);
	}
	if (MenuBtn[BTN_QUIT]->SlideOnHover(xpos, ypos, 3.5f) && Application::IsMousePressed(0) && !isMousePressed)
	{
		isMousePressed = true;
		MenuBtn[BTN_QUIT]->SetbClicked(true);
	}

	if (isMousePressed && !Application::IsMousePressed(0))
	{
		if (MenuBtn[BTN_START]->isHoveredOn(xpos, ypos) && MenuBtn[BTN_START]->getbClicked())
		{
			SceneManager::ChangeScene(SceneManager::SCENE_CITY);
			Application::DisableCursor();
		}
		else
		{
			isMousePressed = false;
			MenuBtn[BTN_START]->SetbClicked(false);
		}
		if (MenuBtn[BTN_CONTROLS]->isHoveredOn(xpos, ypos) && MenuBtn[BTN_CONTROLS]->getbClicked())
		{
		}
		else
		{
			isMousePressed = false;
			MenuBtn[BTN_CONTROLS]->SetbClicked(false);
		}
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

void MainMenu::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(Vector3(0,0,0), Vector3(0,0,1), Vector3(0,1,0));
	renderer->SetToOrtho();

	//renderer->PushTransform();
	renderer->RenderMeshOnScreen(BackGround, 64, 36, 1, 1);
	renderer->RenderMeshOnScreen(Logo, 34, 61, 1, 1);
	//renderer->PopTransform();
	MenuBtn[BTN_START]->Draw(renderer);
	MenuBtn[BTN_CONTROLS]->Draw(renderer);
	MenuBtn[BTN_QUIT]->Draw(renderer);
}

void MainMenu::Exit()
{
	delete renderer;
}

void MainMenu::UpdateMousePos(double xoffset, double yoffset)
{
}
