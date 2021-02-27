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

	void PushStop(Vector3 dest);
	void PushStop(float x, float y, float z);




private:	
	std::vector<Vector3> stops;
	int nextstop;
	float velocity;
	GameObject* door;
	//also puts down the colliders here
	void BuildMeshes(MeshList* meshlist);
};

