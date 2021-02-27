#pragma once
#include "GameObject.h"
#include "NPC.h"
class Train : public NPC
{
public:


	Train(unsigned int id, Mesh* mesh);
	~Train();

	void Update(double dt);

	void Init(MeshList* meshlist, GameObject* lookedAtObj);

	//Push new stop that is 
	Train* PushStop(Vector3 dest);
	Train* PushStop(float x, float y, float z);

	//Create a new stop 
	Train* ExtendStop(Vector3 dest);
	Train* ExtendStop(float x = 0, float y = 0, float z = 0);


	void SetStation();
	//takes the external collision check and does stuff with it
	void SetTransparentCollider(bool collision);

private:	
	std::vector<Vector3> stops;
	std::vector<Vector3> station;
	int nextstop, nextstation;
	float velocity;
	GameObject* door;
	GameObject* collisionboxes;

	bool externalCollider;

	//also puts down the colliders here
	void BuildMeshes(MeshList* meshlist);

	void RotateToObject(Vector3 point);

	int getStationLen();
	int getStopLen();

};

