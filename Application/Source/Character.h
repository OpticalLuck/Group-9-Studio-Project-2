#pragma once
#include "GameObject.h"
#include "Collision.h"

class Character : public GameObject
{ //Child of GameObject

public:
	Character(unsigned int ID, Mesh* mesh);
	~Character();

	void Init(Vector3 position = Vector3(0, 0, 0), 
			  Vector3 rotation = Vector3(0, 0, 0),
			  Vector3 scale = Vector3(1, 1, 1));

	void Update(double dt);

	bool IsWithinRangeOf(GameObject* item);
	int getCollectibleCount();
	bool getSprintState();
	bool getbGrounded();
	bool getbJump();
	float getVertVelocity();
	float getVelocity();

	void setSprintState(bool sprintable);
	void setbGrounded(bool isGrounded);
	void setVertVelocity(float VertVelocity);
	void setVelocity(float Velocity);
	void setbjump(bool isJump);
	void IncrementCollectible();
	void CollisionResolution(GameObject* target);


private:
	static int collectibleCount;
	bool isJump, isGrounded, isSprintable, isGliding;
	float VertVelocity, Velocity;

	Collision* objectStoodOn;

	//private functions

};

