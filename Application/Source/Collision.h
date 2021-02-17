#pragma once
#include "Vector3.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "Renderer.h"

struct Info
{
	Vector3 Axis;
	bool Collided = false;

	Info(Vector3 Axis, bool Collided) {this->Axis = Axis; this->Collided = Collided;};
};

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
	void setRotation(float x, float y, float z);
	//Getter
	Vector3 GetPos();
	Vector3 Gethalfsize();
	Vector3 GetRotation();
	Mesh* GetCollMesh();
	static bool CheckAABBCollision(Collision* box1, Collision* box2);
	static Info CheckOBBCollision(Collision* box1, Collision* box2);
	Vector3 GetFront();
	Vector3 GetUp();
	Vector3 GetRight();
	float getXmin();
	float getXmax();
	float getYmin();
	float getYmax();
	float getZmin();
	float getZmax();
	static float getDiffX(Collision* box1, Collision* box2);
	static float getDiffY(Collision* box1, Collision* box2);
	static float getDiffZ(Collision* box1, Collision* box2);
	static Vector3 getDiff(Vector3 axis, Collision* box1, Collision* box2);
	static float getSeparatingPlane(const Vector3 RPos, const Vector3 Plane, const Collision* box1, const Collision* box2);
	static float ProjectTo(Vector3 axis = Vector3(0, 0, 0), Vector3 box1val = Vector3(0,0,0), Vector3 box2val = Vector3(0, 0, 0));
private:
	Vector3 position;
	Vector3 halfsize;
	Vector3 DefaultHalfSize;

	//x,y,z rotation
	Vector3 Rotation;
	Vector3 Front, Up, Right;

	Mesh* BoxFrame;
};

