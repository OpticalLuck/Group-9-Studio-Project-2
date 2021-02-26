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
	int getRingCount();
	bool getSprintState();
	bool getbGrounded();
	bool getbJump();
	bool getbGlide();
	float getVertVelocity();
	float getVelocity();
	float getStamina();
	GameObject* getWing();

	void setSprintState(bool sprintable);
	void setbGrounded(bool isGrounded);
	void setVertVelocity(float VertVelocity);
	void setVelocity(float Velocity);
	void setStamina(float stamina);
	void setbjump(bool isJump);
	void setbGlide(bool isGliding);
	void setRingCount(int ringCount);
	void IncrementCollectible();
	void CollisionResolution(GameObject* target);


private:
	static int collectibleCount;
	int ringCount;
	bool isJump, isGrounded, isSprintable, isGliding;
	float VertVelocity, Velocity, Stamina;

	GameObject* Wing;

	Collision* objectStoodOn;
	//private functions

};

