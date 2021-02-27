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

	GameObject* getDoor();
	GameObject* getColliderRange();

private:	
	double dt;

	GameObject* lookingatobject;
	GameObject* door;
	GameObject* collisionbox;
	//also puts down the colliders here
	void BuildMeshes(MeshList* meshlist);
};

