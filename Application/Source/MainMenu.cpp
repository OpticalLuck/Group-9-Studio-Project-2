#include "MainMenu.h"
#include "shader.hpp"
#include "SceneManager.h"
#include "MeshBuilder.h"
#include "Application.h"
MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	isInit = true;
	isMousePressed = false;
	MenuBtn[BTN_START] = new Button(64, 45, 4, 1, 10);
	MenuBtn[BTN_START]->SetTexture("Buttons/PlayBtn.tga");
	MenuBtn[BTN_CONTROLS] = new Button(64, 30, 4, 1, 10);
	MenuBtn[BTN_CONTROLS]->SetTexture("Buttons/ControlsBtn.tga");
	MenuBtn[BTN_QUIT] = new Button(64, 15, 4, 1, 10);
	MenuBtn[BTN_QUIT]->SetTexture("Buttons/QuitBtn.tga");
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
	if (MenuBtn[BTN_START]->isHoveredOn(xpos, ypos) && Application::IsMousePressed(0) && !isMousePressed)
	{
		isMousePressed = true;
		MenuBtn[BTN_START]->SetbClicked(true);
	}
	if (MenuBtn[BTN_CONTROLS]->isHoveredOn(xpos, ypos) && Application::IsMousePressed(0) && !isMousePressed)
	{
		isMousePressed = true;
		MenuBtn[BTN_CONTROLS]->SetbClicked(true);
	}
	if (MenuBtn[BTN_QUIT]->isHoveredOn(xpos, ypos) && Application::IsMousePressed(0) && !isMousePressed)
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
