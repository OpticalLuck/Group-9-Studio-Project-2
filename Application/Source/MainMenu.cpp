#include "MainMenu.h"
#include "shader.hpp"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
}

void MainMenu::InitGL()
{
	renderer = new Renderer(0);
}

void MainMenu::Update(double dt)
{
}

void MainMenu::Render()
{
	renderer->Reset();
	renderer->LoadIdentity();
	renderer->SetCamera(Vector3(0,0,0), Vector3(0,0,1), Vector3(0,1,0));
	renderer->SetToOrtho();
}

void MainMenu::Exit()
{
	delete renderer;
}

void MainMenu::UpdateMousePos(double xoffset, double yoffset)
{
}
