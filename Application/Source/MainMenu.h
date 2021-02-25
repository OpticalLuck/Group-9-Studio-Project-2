#pragma once
#include "Scene.h"
#include "Renderer.h"

class MainMenu : public Scene
{
public:
	MainMenu();
	~MainMenu();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;
private:
	Renderer* renderer;
};

