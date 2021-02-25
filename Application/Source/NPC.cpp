#include "NPC.h"
#include "MeshList.h"

//identifier
//x = 0, y = 1, z = 2
float AngleBetween(Vector3 difference, int axis);


NPC::NPC(unsigned int id, Mesh* mesh)
{

	SetMesh(mesh);
	

	canMove = movingToDest = talking = 0;
	objectToLookAt = NULL;
	SetRadius(10.f);
	defaultdirection = GetRotate();
	SetCurrentFlag(FLAG0);
	canDespawn = canRespawn = 0;
	destinationcopy = NULL;
}

NPC::~NPC()
{
	for (int i = 0; i < TOTALPART; i++) {
		delete BodyArr[i];
	}
	delete destinationcopy;
}

void NPC::Update(double dt)
{
	this->dt = dt;
	if (this->getActive()) {
		//if objecttolookat is within range
		if (getCurrentFlag() == FLAG1) {
			//BodyArr[HEAD]->
			Vector3 point = objectToLookAt->GetTranslate() + Vector3(0,3,0);
			Vector3 AxisDir(0, 0, 1);
			Vector3 objectdiff = (point - GetTranslate()).Normalized();
			float currentAngle = BodyArr[HEAD]->GetRotate().y;
			Mtx44 temp;
			temp.SetToRotation(-(GetRotate().y), 0, 1, 0);
			AxisDir = temp * AxisDir;
			temp.SetToRotation(Math::RadianToDegree(atan2(objectdiff.x, objectdiff.z)), 0, 1, 0);
			AxisDir = temp * AxisDir;
			float targetyaw = Math::RadianToDegree(atan2(AxisDir.x, AxisDir.z));
			if (targetyaw < 0)
				targetyaw += 360;

			float smallestyaw = 999.f;
			for (int i = -1; i <= 1; ++i)
			{
				float thisyaw = targetyaw + i * 360.f;
				if (fabs(thisyaw - currentAngle) < fabs(smallestyaw - currentAngle))
				{
					smallestyaw = thisyaw;
				}
			}
			currentAngle = smallestyaw;

			float ROTATIONSPEED = 8 * dt;
			float rotationval;
			std::cout << currentAngle << " " << targetyaw << " ";
			rotationval = (1 - ROTATIONSPEED) * BodyArr[HEAD]->GetRotate().y + ROTATIONSPEED * currentAngle;
			if (BodyArr[HEAD]->GetRotate().y > 360)
			{
				rotationval -= 360;
			}
			else if (BodyArr[HEAD]->GetRotate().y < 0)
			{
				rotationval += 360;
			}
			BodyArr[HEAD]->SetRotate(Vector3(0, rotationval, 0));
			std::cout << rotationval << " " << BodyArr[HEAD]->GetRotate().y << std::endl;
		}
		else {
			RotateToVector(BodyArr[HEAD], Vector3(0,0,0));
			
			if (!destinations.empty()) { //Stop moving when all destinations reached
				
				float angleToPoint = GetAngleToPoint(destinations.front());
				float offsetangle = 0.9f;
				if (GetRotate().y < angleToPoint - offsetangle || GetRotate().y > angleToPoint + offsetangle) {
					float ROTATIONSPEED = 2 * dt;
					float rotationval;

					rotationval = (1 - ROTATIONSPEED) * GetRotate().y + ROTATIONSPEED * GetAngleToPoint(destinations.front());
					if (GetRotate().y > 360)
					{
						rotationval -= 360;
					}
					else if (GetRotate().y < 0)
					{
						rotationval += 360;
					}
					SetRotate(Vector3(0, rotationval, 0));
				}
				else {
					MoveToPos(destinations.front());
					if (abs((GetTranslate() - destinations.front()).Length()) < 1) {
						doDespawn();
						destinations.pop();
					}
				}
			}
			else {
				SetCurrentFlag(FLAG1);
			}

		}




	}

	
	doRespawn();
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
	if (!canDespawn)
		destinations.push(position);
	else {
		std::cout << "Path point not set! Please path it out properly before you push your despawn point!\n";
	}
}

void NPC::PushPathPoint(float x, float y, float z)
{
	PushPathPoint(Vector3(x, y, z));
}

void NPC::PushDespawnPoint(Vector3 position)
{
	destinations.push(position);
	canDespawn = true;
}

void NPC::PushDespawnPoint(float x, float y, float z)
{
	PushDespawnPoint(Vector3(x, y, z));
}

void NPC::SetRespawnPos(Vector3 position)
{
	if (canDespawn) {
		if (destinationcopy == NULL) {
			destinationcopy = new std::queue<Vector3>;
			*destinationcopy = destinations;
		}
		respawnpos = position;
		canRespawn = true;
	}
	else {
		std::cout << "Respawn point not set! Did you set the respawn point before pushing the despawn?\n";
	}

}


void NPC::SetRespawnPos(float x, float y, float z)
{
	SetRespawnPos(Vector3(x, y, z));
}

void NPC::BuildMeshes(MeshList* meshlist)
{
	//allocate all to NULL incase any parts unused
	//can remove if all are used
	for (int i = 0; i < TOTALPART; i++) {
		BodyArr[i] = NULL;
	}

	BodyArr[HEAD] = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_HEAD));
	BodyArr[HEAD]->SetTranslate(Vector3(0,1.8,0));
	this->AddChild(BodyArr[HEAD]); 

}




float NPC::GetAngleToPoint(Vector3 point)
{
	

	Vector3 AxisDir(0, 0, 1);
	
	Vector3 objectdiff = (point - GetTranslate()).Normalized();
	float currentAngle = GetRotate().y;
	Mtx44 temp;
	temp.SetToRotation(Math::RadianToDegree(atan2(objectdiff.x, objectdiff.z)), 0, 1, 0);
	AxisDir = temp * AxisDir;
	float targetyaw = Math::RadianToDegree(atan2(AxisDir.x, AxisDir.z));
	if (targetyaw < 0)
		targetyaw += 360;

	float smallestyaw = 999.f;
	for (int i = -1; i <= 1; ++i)
	{
		float thisyaw = targetyaw + i * 360.f;
		if (fabs(thisyaw - currentAngle) < fabs(smallestyaw - currentAngle))
		{
			smallestyaw = thisyaw;
		}
	}
	currentAngle = smallestyaw;

	return currentAngle;
	

}





void NPC::RotateTowardsCharacter(GameObject* parttorotate, float maximumangle, float maxX)
{

	//Reset the origin
	Mtx44 rotationx, rotationy, rotationz;
	rotationx.SetToRotation(-(GetRotate().x), 1, 0, 0);
	rotationy.SetToRotation(-GetRotate().y, 0, 1, 0);
	rotationz.SetToRotation(-(GetRotate().z), 0, 0, 1);
	
	Vector3 objectdiff = (objectToLookAt->GetTranslate() + Vector3(0,2.5,0) - (BodyArr[HEAD]->GetTranslate() + GetTranslate())) ;
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
	//y angle boundaries
	if ( (yangle < -maximumangle && yangle > -180)) {
		yangle = -maximumangle;
	}
	else if ((yangle > maximumangle && yangle < 180)) {
		yangle = maximumangle;
	}

	float xangle = AngleBetween(objectdiffx, 0);

	if ((xangle < -maxX)) {
		xangle = -maxX;
	}
	else if (xangle > maxX) {
		xangle = maxX;
	}

	//std::cout << yangle << std::endl;
	RotateToVector(parttorotate, Vector3(0, yangle, 0));
}

void NPC::RotateToVector(GameObject* parttorotate, Vector3 rotate)
{
	float partx, party, partz, rotSPEED;
	partx = parttorotate->GetRotate().x;
	party = parttorotate->GetRotate().y;
	partz = parttorotate->GetRotate().z;
	rotSPEED = 1.f;
	

	if (party < rotate.y - 1) {
		party += rotSPEED * dt;
	}
	else if (party > rotate.y + 1) {
		std::cout <<  "hi" << "\n";
		party -= rotSPEED * dt;
	}

	if (partx < rotate.x - 1) {
		partx += rotSPEED * dt;
	}
	else if (partx > rotate.x + 1) {
		partx -= rotSPEED * dt;
	}

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

	currentpos = currentpos + view * 10.f * dt;
	this->SetTranslate(currentpos);
}

void NPC::doRespawn()
{
	if (canDespawn && destinations.empty() && !this->getActive() && canRespawn) {
		this->SetTranslate(respawnpos);
		destinations = *destinationcopy;

		this->SetActive(true);
	}
}

void NPC::doDespawn()
{
	if (canDespawn && destinations.back() == destinations.front()) { //if on the last destination (despawn location)
		this->SetActive(false);
	}

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