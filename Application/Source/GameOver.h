#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Button.h"

class GameOver : public Scene
{
public:
	GameOver();
	~GameOver();

	virtual void Init();
	virtual void InitGL();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void UpdateMousePos(double xoffset, double yoffset) override;

	enum BTN_NAME
	{
		BTN_QUIT,
		BTN_TOTAL
	};

private:
	Renderer* renderer;

	Mesh* Background;
	Mesh* TheEnd;
	Button* MenuBtn[BTN_TOTAL];
	bool isMousePressed;
};

