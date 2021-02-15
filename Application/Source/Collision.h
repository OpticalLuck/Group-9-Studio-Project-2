#pragma once
#include "Vector3.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "Renderer.h"

class Collision
{
public:
	Collision();
	Collision(Vector3 position, Vector3 halfsize);
	~Collision();

	void DrawFrame(Renderer* renderer);
	//Mutator
	void setcollpos(Vector3 position);
	void sethalfsize(Vector3 halfsize);

	//Getter
	Vector3 GetPos();
	Vector3 Gethalfsize();
	Mesh* GetCollMesh();
	static bool CheckCollision(Collision* box1, Collision* box2);
	float getXmin();
	float getXmax();
	float getYmin();
	float getYmax();
	float getZmin();
	float getZmax();
	static float getDiffX(Collision* box1, Collision* box2);
	static float getDiffY(Collision* box1, Collision* box2);
	static float getDiffZ(Collision* box1, Collision* box2);

private:
	Vector3 position;
	Vector3 halfsize;
	
	Mesh* BoxFrame;

};

