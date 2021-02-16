#include "NPC.h"
#include "MeshList.h"


NPC::NPC(unsigned int id, Mesh* mesh)
{
	BuildMeshes(mesh);

	canMove = talking = 0;
	objectToLookAt = NULL;
	radius = 40.f;
}

NPC::~NPC()
{
	for (int i = 0; i < TOTALPART; i++) {
		delete BodyArr[i];
	}
}

void NPC::Update(double dt)
{
	if (canMove || true) {

		//if objecttolookat is within range
		if (true) {
			//BodyArr[HEAD]->
			
			//Reset the origin
			Mtx44 rotation;
			rotation.SetToRotation(GetRotate().x, 1, 0, 0);
			rotation.SetToRotation(GetRotate().y, 0, 1, 0);
			rotation.SetToRotation(GetRotate().z, 0, 0, 1);
			Vector3 objectdiff = (objectToLookAt->GetTranslate() - GetTranslate()).Normalized();
			//move object to be at tested position for calculations
			objectdiff = rotation * objectdiff;

			//about the y axis
			float ycosine = objectdiff.x;
			float ytangent = objectdiff.z / objectdiff.x;
			float yangle = Math::RadianToDegree(std::atanf(ytangent));
			std::cout << GetRotate().y << "\n";
			if (yangle < 0) {
				yangle = 180 + yangle;
			}

			SetRotate(Vector3(0, yangle, 0));
			//yangle = Math::Clamp(yangle, 0.f, 100.f);
			/*
			Mtx44 rotation;
			rotation.SetToRotation(-baseYrot, 0, 1, 0);
			Vector3 temppos = (campos - position);
			temppos = rotation * temppos;
			float cosine = (temppos.x);
			float forwardgrad = (temppos.z) / cosine;
			float yanglediff = Math::RadianToDegree(std::atan(forwardgrad));
		
			if ((forwardgrad * cosine) < 0) {
				yanglediff = -yanglediff ;
			}

			

			//rotation.SetToRotation(-(yanglediff + 270), 0, 1, 0);
			//forward = rotation * forward;
			//std::cout << temppos.x << " " << temppos.y << " " << temppos.z  << "\n";
			SetRotation(Vector3(0, -(yanglediff+270), 0));
			
			*/


		}

	}
}

bool NPC::inRadius()
{
	return false;
}

void NPC::SetObjectToLookAt(GameObject* obj)
{
	objectToLookAt = obj;
}

void NPC::BuildMeshes(Mesh* mesh)
{
	//allocate all to NULL incase any parts unused
	//can remove if all are used
	for (int i = 0; i < TOTALPART; i++) {
		BodyArr[i] = NULL;
	}

	SetMesh(mesh);

	//get body parts
	MeshList meshlist;

	BodyArr[HEAD] = new GameObject(GetID(), meshlist.GetMesh(MeshList::MESH_HEAD));
	AddChild(BodyArr[HEAD]);
}
