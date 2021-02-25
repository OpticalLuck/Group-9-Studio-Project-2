#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Button.h"

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

	enum BTN_NAME
	{
		BTN_START = 0,
		BTN_CONTROLS,
		BTN_QUIT,
		BTN_TOTAL
	};
private:
	Renderer* renderer;
	Button* MenuBtn[BTN_TOTAL];
	bool isMousePressed;
};

