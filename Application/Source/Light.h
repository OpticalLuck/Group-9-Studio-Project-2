#pragma once
#include "Vertex.h"
#include "MatrixStack.h"

class Light
{
public:
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	enum UNIFORM_TYPE
	{
		U_LIGHT_POSITION,
		U_LIGHT_COLOR,
		U_LIGHT_POWER,
		U_LIGHT_KC,
		U_LIGHT_KL,
		U_LIGHT_KQ,
		U_LIGHT_TYPE,
		U_LIGHT_SPOTDIRECTION,
		U_LIGHT_COSCUTOFF,
		U_LIGHT_COSINNER,
		U_LIGHT_EXPONENT,
		U_TOTAL
	};
	LIGHT_TYPE type;
	Vector3 position;
	Color color;
	float power;
	float kC, kL, kQ;
	float cosCutoff;
	float cosInner;
	float exponent;
	Vector3 spotDirection;

	unsigned parameters[U_TOTAL];
	int index;
	//to do: add a constructor

	Light(unsigned m_programID, int count);

	void Set(LIGHT_TYPE type, Vector3 pos, Color color, float power, float kC, float kL, float kQ, Vector3 spotDirection);
	void Mode(int LIGHT_TYPE);
};
