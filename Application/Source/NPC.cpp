#include "NPC.h"
#include "MeshList.h"


NPC::NPC(unsigned int id, Mesh* mesh)
{

	SetMesh(mesh);
	

	canMove = movingToDest = talking = 0;
	objectToLookAt = NULL;
	SetRadius(10.f);
	defaultdirection = GetRotate();
	

}

NPC::~NPC()
{
	for (int i = 0; i < TOTALPART; i++) {
		delete BodyArr[i];
	}
}

void NPC::Update(double dt)
{
	this->dt = dt;
	
	if (canMove || true) {

		//if objecttolookat is within range
		if (getCurrentFlag() == FLAG1) {
			//BodyArr[HEAD]->
			//RotateTowardsCharacter(BodyArr[HEAD], 90.f);
			std::cout << abs((GetTranslate() - destinations.front()).Length()) << "\n";
		}
		else if (getCurrentFlag() == FLAG4) {
		}
		else {
			RotateToVector(BodyArr[HEAD], Vector3(0,0,0));
			
			RotateToPoint(destinations.front());
			MoveInDir(defaultdirection);
		}
	}
}

void NPC::Init(MeshList* meshlist, GameObject* lookedAtObj, Vector3 pos, Vector3 rot, Vector3 scale, float radius)
{
	BuildMeshes(meshlist);
	SetTranslate(pos);
	
	SetDefaultDir(rot);
	SetScale(scale);
	SetRadius(radius);
	SetObjectToLookAt(lookedAtObj);
}






void NPC::SetObjectToLookAt(GameObject* obj)
{
	objectToLookAt = obj;
}

void NPC::SetDefaultDir(Vector3 def)
{
	defaultdirection = def;
	SetRotate(def);
}

void NPC::PushPathPoint(Vector3 position)
{
	destinations.push(position);
}

void NPC::PushPathPoint(float x, float y, float z)
{
	PushPathPoint(Vector3(x, y, z));
}

void NPC::BuildMeshes(MeshList* meshlist)
{
	//allocate all to NULL incase any parts unused
	//can remove if all are used
	for (int i = 0; i < TOTALPART; i++) {
		BodyArr[i] = NULL;
	}

	BodyArr[HEAD] = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_HEAD));
	BodyArr[LARM] = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_HEAD));
	BodyArr[RARM] = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_HEAD));
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

void NPC::RotateToPoint(Vector3 point)
{
	//Mtx44 rotationx, rotationy, rotationz;
	//rotationx.SetToRotation(-(GetRotate().x), 1, 0, 0);
	//rotationy.SetToRotation(-GetRotate().y, 0, 0.98, 0);
	////rotationz.SetToRotation(-(GetRotate().z), 0, 0, 1);

	Vector3 objectdiff = (point - GetTranslate()).Normalized();
	////move object to be at tested position for calculations
	////Vector3 rotate = GetRotate();
	//Vector3 objectdiffx = rotationx * objectdiff;
	//Vector3 objectdiffy = rotationy * objectdiff;
	////Vector3 objectdiffz = rotationz * objectdiff;
	////Move projected object with position



	////calculations 


	float yangle = AngleBetween(objectdiff, 1) + 90;

	//std::cout << yangle << "\n";
	Mtx44 rotationx;
	////x angle bounds move with y angle
	rotationx.SetToRotation(-yangle, 0, 1, 0);
	//objectdiffx = rotationx * objectdiffx;
	//objectdiffx = rotationy * objectdiffx;

	//

	//float xangle = AngleBetween(objectdiffx, 0);
	RotateToVector(this, Vector3(0, yangle, 0));


}





void NPC::RotateTowardsCharacter(GameObject* parttorotate, float maximumangle)
{

	//Reset the origin
	Mtx44 rotationx, rotationy, rotationz;
	rotationx.SetToRotation(-(GetRotate().x), 1, 0, 0);
	rotationy.SetToRotation(-GetRotate().y, 0, 1, 0);
	rotationz.SetToRotation(-(GetRotate().z), 0, 0, 1);
	
	Vector3 objectdiff = (objectToLookAt->GetTranslate() - (BodyArr[HEAD]->GetTranslate() + GetTranslate())) ;
	//move object to be at tested position for calculations
	
	//Vector3 rotate = GetRotate();
	Vector3 objectdiffx = rotationx * objectdiff;
	Vector3 objectdiffy = rotationy * objectdiff;
	Vector3 objectdiffz = rotationz * objectdiff;
	//Move projected object with position
	


	//calculations 


	float yangle = AngleBetween(objectdiffy, 1) + 90;
	

	//x angle bounds move with y angle
	rotationx.SetToRotation(-yangle, 0, 1, 0);
	objectdiffx = rotationx * objectdiffx;
	objectdiffx = rotationy * objectdiffx;
	std::cout << GetRotate().y << "\n";
	//y angle boundaries
	if ( (yangle < -maximumangle && yangle > -180)) {
		yangle = -maximumangle;
	}
	else if ((yangle > maximumangle && yangle < 180)) {
		yangle = maximumangle;
	}

	float xangle = AngleBetween(objectdiffx, 0);
	RotateToVector(parttorotate, Vector3(xangle, yangle, 0));
}

void NPC::RotateToVector(GameObject* parttorotate, Vector3 rotate)
{
	float partx, party, partz, rotSPEED;
	partx = parttorotate->GetRotate().x;
	party = parttorotate->GetRotate().y;
	partz = parttorotate->GetRotate().z;
	rotSPEED = 100.f;
	

	if (party < rotate.y - 1) {
		party += rotSPEED * dt;
	}
	else if (party > rotate.y + 1) {
		party -= rotSPEED * dt;
	}

	if (partx < rotate.x - 1) {
		partx += rotSPEED * dt;
	}
	else if (partx > rotate.x + 1) {
		partx -= rotSPEED * dt;
	}

	//std::cout << party << " ";
	parttorotate->SetRotate(Vector3(partx, party, partz));
}

void NPC::MoveInDir(Vector3 rot)
{
	Mtx44 rotation;
	rotation.SetToRotation(rot.y, 0, 1, 0);

	Vector3 direction(0,0,1);
	direction = rotation * direction;

	Vector3 part;
	part.x = GetTranslate().x;
	part.y = GetTranslate().y;
	part.z = GetTranslate().z;

	part = part + direction * dt;

	this->SetTranslate(part);
}

void NPC::MoveToPos(Vector3 pos)
{
	Vector3 currentpos = GetTranslate();
	Vector3 view = (pos - currentpos).Normalized();

	currentpos = currentpos + view * dt;
	this->SetTranslate(currentpos);
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

	//std::cout << tangent << "\n";
	
	if (cosine < 0 ) {
		angle = 180 + angle;
	}



	return -angle;
}