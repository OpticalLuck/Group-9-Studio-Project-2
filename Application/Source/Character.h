#pragma once
#include "GameObject.h"
#include "Collision.h"
#include "CameraVer2.h"

class Character : public GameObject
{ //Child of GameObject

public:
	Character(unsigned int ID, Mesh* mesh);
	~Character();

	void Init(Vector3 position = Vector3(0, 0, 0), 
			  Vector3 rotation = Vector3(0, 0, 0),
			  Vector3 scale = Vector3(1, 1, 1));

	void Update(CameraVer2* camera, double dt);

	bool IsWithinRangeOf(GameObject* item);
	int getCollectibleCount();
	void IncrementCollectible();

private:
	static int collectibleCount;
	bool isJump, isGrounded;
	float VertVelocity;
};

