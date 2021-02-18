#pragma once
#include "Vector3.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "Renderer.h"

struct Info
{
	Vector3 Axis; //Stores Axis with shortest intersection
	float distance; //Stores shortest distance of the intersection
	bool Collided = false;

	Info(Vector3 Axis, float distance, bool Collided) { this->Axis = Axis; this->Collided = Collided; this->distance = distance; };
};

class GameObject;

class Collision
{
public:

	Collision();
	Collision(Vector3 position, Vector3 halfsize);
	~Collision();

	void DrawFrame(Renderer* renderer);
	//Mutator
	void setTranslate(Vector3 position);
	void sethalfsize(Vector3 halfsize);
	void setRotation(Vector3 rotation);
	static void OBBResolution(GameObject* object, GameObject* target);
	//Getter
	Vector3 GetPos();
	Vector3 Gethalfsize();
	Vector3 GetRotation();
	Mesh* GetCollMesh();
	static Info CheckOBBCollision(Collision* box1, Collision* box2);
	Vector3 GetFront();
	Vector3 GetUp();
	Vector3 GetRight();

	static Vector3 getDiff(Vector3 axis, Collision* box1, Collision* box2);
	static float getSeparatingPlane(const Vector3 RPos, const Vector3 Plane, const Collision* box1, const Collision* box2);

private:
	Vector3 position;
	Vector3 halfsize;
	Vector3 DefaultHalfSize;

	//x,y,z rotation
	Vector3 Rotation;
	Vector3 Front, Up, Right;

	Mesh* BoxFrame;
};

