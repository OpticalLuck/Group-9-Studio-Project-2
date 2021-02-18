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
			RotateTowardsCharacter(BodyArr[HEAD], dt, 100.f);
			


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
	BodyArr[LARM] = new GameObject(GetID(), meshlist.GetMesh(MeshList::MESH_HEAD));
	BodyArr[RARM] = new GameObject(GetID(), meshlist.GetMesh(MeshList::MESH_HEAD));
	this->AddChild(BodyArr[HEAD]); 
	BodyArr[HEAD]->AddChild(BodyArr[LARM]);
	BodyArr[HEAD]->AddChild(BodyArr[RARM]);
	BodyArr[HEAD]->SetTranslate(Vector3(0,0,1));
	BodyArr[HEAD]->SetScale(Vector3(1,1,0.5));
	BodyArr[LARM]->SetTranslate(Vector3(0,0,1));
	BodyArr[RARM]->SetTranslate(Vector3(0,1,0));
}

//identifier
//x = 0, y = 1, z = 2
float AngleBetween(Vector3 difference, int axis);



void NPC::RotateTowardsCharacter(GameObject* parttorotate, double dt, float maximumangle)
{

	//Reset the origin
	Mtx44 rotationx, rotationy, rotationz;
	//rotmatrix.SetToIdentity();
	rotationx.SetToRotation(-(GetRotate().x), 1, 0, 0);
	rotationy.SetToRotation(-GetRotate().y, 0, 1, 0);
	rotationz.SetToRotation(-(GetRotate().z), 0, 0, 1);
	
	Vector3 objectdiff = (objectToLookAt->GetTranslate() - BodyArr[HEAD]->GetTranslate());
	//move object to be at tested position for calculations
	
	//Vector3 rotate = GetRotate();
	Vector3 objectdiffx = rotationx * objectdiff;
	Vector3 objectdiffy = rotationy * objectdiff ;
	Vector3 objectdiffz = rotationz * objectdiff;


	//calculations 


	float yangle = AngleBetween(objectdiffy, 1) + 90;
	
	//std::cout << yangle << "\n";

	

	//y angle boundaries
	if ( (yangle < -maximumangle && yangle > -180)) {
		yangle = -maximumangle;
	}
	else if ((yangle > maximumangle && yangle < 180)) {
		yangle = maximumangle;
	}
	//x angle bounds move with y angle
	rotationx.SetToRotation(-yangle, 0, 1, 0);
	objectdiffx = rotationx * objectdiffx;
	
	
	
	float xangle = AngleBetween(objectdiffx, 0);

	//parttorotate->SetRotate(Vector3(xangle, yangle , 0));
	float partx, party, partz, rotSPEED;
	partx = parttorotate->GetRotate().x;
	party = parttorotate->GetRotate().y;
	partz = parttorotate->GetRotate().z;
	rotSPEED = 100.f;


	if (party < yangle - 1) {
		party += rotSPEED * dt;
	}
	else if (party > yangle + 1) {
		party -= rotSPEED * dt;
	}

	if (partx < xangle - 1) {
		partx += rotSPEED * dt;
	}
	else if (partx > xangle + 1) {
		partx -= rotSPEED * dt;
	}


	parttorotate->SetRotate(Vector3(partx, party, partz));
	

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
		cosine = difference.z;
	}

	float tangent = sine / cosine;
	float angle = Math::RadianToDegree(std::atanf(tangent));

	
	
	if (cosine < 0 ) {
		//std::cout << "nice" << "\n";
		angle = 180 + angle;
	}



	return -angle;
}