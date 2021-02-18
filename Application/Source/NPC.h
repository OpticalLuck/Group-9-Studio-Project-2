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

class NPC : public GameObject 
{
public:
	//NPC is the body
	NPC(unsigned int id, Mesh* mesh);
	~NPC();
	
	void Update(double dt);
	

	bool inRadius();
	//Sets the ObjectToLookAt to allow for calculations revolving around looking
	void SetObjectToLookAt(GameObject* obj);

	enum BODYPART
	{
		HEAD,
		LARM,
		RARM,
		TOTALPART
	};

private:
	

	bool canMove, talking;
	float radius;
	//Vector3 defaultdirection;
	//Bunch of words they will say
	std::vector<std::string> speech;
	//Array pointer pointing to each part as a seperate gameobj
	GameObject* BodyArr[TOTALPART];
	//Refers to the object it mainly interacts with
	GameObject* objectToLookAt;

	void BuildMeshes(Mesh* mesh);

	//Smaller Functions for small processes

	//Rotate gameobj part towards character
	//Maximum angle is how many degrees from the front they can move.	
	//cannot be more than 180	
	void RotateTowardsCharacter(GameObject* parttorotate, double dt ,float maximumangle = 180 );
};