//Child of GameObject
/*
=== NPCs HAVE ===
1. MOVEMENT
2. APPEARANCE
3. DIALOGUE

=================
*/
#pragma once
#include "GameObject.h"
#include "MeshList.h"
#include <string>
#include <queue>

class NPC : public GameObject 
{
public:
	NPC();
	NPC(unsigned int id, Mesh* mesh);
	~NPC();
	
	void Update(double dt);
	
	//A much needed function after creating an NPC
	void Init(MeshList* meshlist,
			  GameObject* lookedAtObj,
			  Vector3 pos = Vector3(0,0,0),
			  Vector3 rot = Vector3(0,0,0), 
		      Vector3 scale = Vector3(1,1,1),
			  float radius = 10.f);

	//Sets the ObjectToLookAt to allow for calculations revolving around looking
	void SetObjectToLookAt(GameObject* obj);
	//Rotation vector that they will always be in
	void SetDefaultDir(Vector3 def);
	//Position they'll flock to when idle (if set)
	void SetDefaultPos(Vector3 def);

	//add a point to go towards
	//try to keep them on the same y level and straight (only affect one axis at a time)
	void PushPathPoint(Vector3 position);
	void PushPathPoint(float x, float y, float z);

	//make npc despawn at this position
	void PushDespawnPoint(Vector3 position);
	void PushDespawnPoint(float x, float y, float z);

	void SetRespawnPos(Vector3 position);
	void SetRespawnPos(float x, float y, float z);


	void BuildMeshes(MeshList* meshlist);
	
	

	enum BODYPART
	{
		HEAD,
		TOTALPART
	};

private:
	
	

	bool talking, movingToDest;
	Vector3 defaultdirection, defaultposition;
	//Bunch of words they will say
	std::vector<std::string> speech;
	//Array pointer pointing to each part as a seperate gameobj
	GameObject* BodyArr[TOTALPART];
	//Refers to the object it mainly interacts with
	
	std::queue<Vector3> destinations;
	

	std::queue<Vector3>* destinationcopy;

	bool canDespawn, canRespawn;
	Vector3 respawnpos;


	//Smaller Functions for small processes

	//Rotate NPC
	

	//Rotate bodypart towards character
	//Maximum angle is how many degrees from the front they can move.	
	//cannot be more than 180	
	void RotateTowardsCharacter(GameObject* parttorotate,float maximumangle = 180, float maxX = 30 );
	void RotateToVector(GameObject* parttorotate, Vector3 rotate);

	

	//Spawns the player here and activates it
	void doRespawn();
	//Despawns the player. Deactivates it.
	void doDespawn();

protected:

	double dt;
	GameObject* objectToLookAt;
	bool DefaultIdleSet;

	float GetAngleToPoint(Vector3 point);
	//Move Towards the rotation vector somehow
	void MoveInDir(Vector3 rot);
	//Move Towards a destination
	void MoveToPos(Vector3 pos, float speed = 6.f);
	//Linearly Interpolate towards a point
	void LerpToPos(Vector3 pos, float speed = 8.0f);
};