#pragma once
#include "GameObject.h"
class SkyBox
{
public:
	enum FACES
	{
		F_FRONT,
		F_BACK,
		F_TOP,
		F_BOTTOM,
		F_LEFT,
		F_RIGHT,
		F_TOTAL
	};
	SkyBox();
	~SkyBox();

	void Draw(Renderer* renderer);
private:
	GameObject* faces[F_TOTAL];
};