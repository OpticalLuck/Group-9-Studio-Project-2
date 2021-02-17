#include "NPC.h"
#include "MeshList.h"


NPC::NPC(unsigned int id, Mesh* mesh)
{
	BuildMeshes(mesh);

	canMove = talking = 0;
	objectToLookAt = NULL;
	radius = 40.f;
	//defaultdirection = GetRotate();
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
	BodyArr[LARM] = new GameObject(GetID(), meshlist.GetMesh(MeshList::MESH_HEAD));
	BodyArr[HEAD]->AddChild(BodyArr[LARM]);
	BodyArr[HEAD]->SetTranslate(Vector3(0,0,1));
	BodyArr[LARM]->SetTranslate(Vector3(1,0,0));
}

//identifier
float AngleBetween(Vector3 difference, int axis);

void NPC::RotateTowardsCharacter()
{

	//Reset the origin
	Mtx44 rotation;
	rotation.SetToRotation(-GetRotate().x, 1, 0, 0);
	rotation.SetToRotation(-GetRotate().y, 0, 1, 0);
	rotation.SetToRotation(-GetRotate().z, 0, 0, 1);
	Vector3 objectdiff = (objectToLookAt->GetTranslate() - BodyArr[HEAD]->GetTranslate());
	//move object to be at tested position for calculations
	objectdiff = rotation * objectdiff;

	//calculations about the y axis
	
	float xangle = AngleBetween(objectdiff, 0);
	float yangle = AngleBetween(objectdiff, 1);
	float zangle = AngleBetween(objectdiff, 2);

	BodyArr[HEAD]->SetRotate(Vector3(xangle, 0, 0));

}

// 0 = X, 1 = Y, 2 = Z
float AngleBetween(Vector3 difference, int axis) {

	enum AXIS {
		RIGHT,
		UP, 
		VIEW,
	};

	float sine, cosine;

	axis = axis % 3;
	if (axis == RIGHT) {
		//float xtangent = difference.x / difference.z;
		sine = difference.y;
		cosine = difference.z;
	}
	else if (axis == UP) {
		sine = difference.z;
		cosine = difference.x;
	}
	else {
		sine = difference.y;
		cosine = difference.x;
	}

	float tangent = sine / cosine;
	float angle = Math::RadianToDegree(std::atanf(tangent));
	if (sine < 0) {

		angle = -angle;
	}

	if (cosine < 0) {
		std::cout << "nice" << "\n";
		angle = 180 + angle;
	}



	return -angle;
}