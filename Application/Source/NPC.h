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
	//NPC is the body
	NPC(unsigned int id, Mesh* mesh);
	~NPC();
	
	void Update(double dt);
	
	//A much needed function after creating an NPC
	void Init(MeshList* meshlist,
			  GameObject* lookedAtObj,
			  Vector3 pos,
			  Vector3 rot = Vector3(0,0,0), 
		      Vector3 scale = Vector3(1,1,1),
			  float radius = 10.f);

	//Sets the ObjectToLookAt to allow for calculations revolving around looking
	void SetObjectToLookAt(GameObject* obj);
	void SetDefaultDir(Vector3 def);

	//add a point to go towards
	//try to keep them on the same y level and straight (only affect one axis at a time)
	void PushPathPoint(Vector3 position);
	void PushPathPoint(float x, float y, float z);

	

	enum BODYPART
	{
		HEAD,
		LARM,
		RARM,
		TOTALPART
	};

private:
	
	double dt;

	bool canMove, talking;
	Vector3 defaultdirection;
	//Bunch of words they will say
	std::vector<std::string> speech;
	//Array pointer pointing to each part as a seperate gameobj
	GameObject* BodyArr[TOTALPART];
	//Refers to the object it mainly interacts with
	GameObject* objectToLookAt;
	std::queue<Vector3> destinations;



	void BuildMeshes(MeshList* meshlist);

	//Smaller Functions for small processes

	//Rotate NPC
	void RotateToPoint(Vector3 point);

	//Rotate bodypart towards character
	//Maximum angle is how many degrees from the front they can move.	
	//cannot be more than 180	
	void RotateTowardsCharacter(GameObject* parttorotate,float maximumangle = 180 );
	void RotateToVector(GameObject* parttorotate, Vector3 rotate);

	//Move Towards the rotation vector somehow
	void MoveInDir(Vector3 rot);
	//Move Towards a destination
	void MoveToPos(Vector3 pos);
};