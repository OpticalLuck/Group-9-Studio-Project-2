#include "NPC.h"
#include "MeshList.h"

//identifier
//x = 0, y = 1, z = 2
float AngleBetween(Vector3 difference, int axis);
float lerp(float a, float b, float t);

NPC::NPC()
{
	DefaultIdleSet = movingToDest = talking = 0;
	objectToLookAt = NULL;
	canDespawn = canRespawn = 0;
	defaultdirection = GetRotate();
	destinationcopy = NULL;
}

NPC::NPC(unsigned int id, Mesh* mesh)
{

	SetMesh(mesh);
	

	DefaultIdleSet = movingToDest = talking = 0;
	objectToLookAt = NULL;
	SetRadius(5.f);
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
			RotateTowardsCharacter(BodyArr[HEAD], 75, 180); //50);
			//RotateToVector(BodyArr[HEAD], Vector3(0,0,0));
		}
		else {
			RotateToVector(BodyArr[HEAD], GetRotate());
			
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
						LerpToPos(destinations.front(), 10.f);
						
						doDespawn();
						destinations.pop();
					}
					else {
					}
				}
			}
			else if (DefaultIdleSet && GetTranslate() != defaultposition) {
				
				//MoveToPos(defaultposition);
				LerpToPos(defaultposition);
			}

			else {
				float angleToPoint = defaultdirection.y; //GetAngleToPoint(defaultposition + Vector3(0,0,1));
				float ROTATIONSPEED = 2 * dt;
				float rotationval;

				rotationval = (1 - ROTATIONSPEED) * GetRotate().y + ROTATIONSPEED * angleToPoint;
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

void NPC::SetDefaultPos(Vector3 def)
{
	defaultposition = def;
	DefaultIdleSet = true;
	SetTranslate(def);
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
	if (DefaultIdleSet) { //don't set a despawn point if have a default position
		std::cout << "If you have a default idle set, would you really want to despawn your NPC?\n";
		return;
	}


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



	Vector3 point = objectToLookAt->GetTranslate() +Vector3(0, 2.5, 0);
	Vector3 AxisDir(0, 0, 1);
	Vector3 objectdiff = (point - (GetTranslate() + Vector3(0, 1.8, 0))).Normalized();
	float currentAngle = parttorotate->GetRotate().y;
	Mtx44 temp;
	temp.SetToRotation(-(GetRotate().y), 0, 1, 0);
	AxisDir = temp * AxisDir;
	temp.SetToRotation(Math::RadianToDegree(atan2(objectdiff.x, objectdiff.z)), 0, 1, 0);
	AxisDir = temp * AxisDir;
	float targetyaw = Math::RadianToDegree(atan2(AxisDir.x, AxisDir.z));
	if (targetyaw < 0)
		targetyaw += 360;

	if (targetyaw > maximumangle && targetyaw < 180) {
		targetyaw = maximumangle;
	}
	else if (targetyaw < 360 - maximumangle && targetyaw > 180) {
		targetyaw = 360 - maximumangle;
	}
	
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
	rotationval = (1 - ROTATIONSPEED) * parttorotate->GetRotate().y + ROTATIONSPEED * currentAngle;
	if (parttorotate->GetRotate().y > 360)
	{
		rotationval -= 360;
	}
	else if (parttorotate->GetRotate().y < 0)
	{
		rotationval += 360;
	}

	

	AxisDir = Vector3(0, 0, 1);
	currentAngle = parttorotate->GetRotate().x;
	temp.SetToRotation(-rotationval, 0, 1, 0);
	AxisDir = temp * AxisDir;


	objectdiff = temp * objectdiff;
	temp.SetToRotation(-(GetRotate().y), 0, 1, 0);
	objectdiff = temp * objectdiff;
	std::cout << objectdiff.y << "," << objectdiff.z << "\n";
	temp.SetToRotation(-(GetRotate().y), 0, 1, 0);
	temp.SetToRotation(Math::RadianToDegree(atan2(objectdiff.y, abs(objectdiff.z))), 1, 0, 0);
	AxisDir = temp * AxisDir;

	float targetpitch = Math::RadianToDegree(atan2(AxisDir.y, AxisDir.z));
	if (targetpitch < 0)
		targetpitch += 360;
	if (targetpitch > maxX && targetpitch < 180) {
		targetpitch = maxX;
	}
	else if (targetpitch < 360 - maxX && targetpitch > 180) {
		targetpitch = 360 - maxX;
	}

	float smallestpitch = 999.f;
	for (int i = -1; i <= 1; ++i)
	{
		float thispitch = targetpitch + i * 360.f;
		if (fabs(thispitch - currentAngle) < fabs(smallestpitch - currentAngle))
		{
			smallestpitch = thispitch;
		}
	}
	currentAngle = smallestpitch;

	float rotationxval;
	rotationxval = (1 - ROTATIONSPEED) * parttorotate->GetRotate().x + ROTATIONSPEED * currentAngle;
	if (parttorotate->GetRotate().x > 360)
	{
		rotationxval -= 360;
	}
	else if (parttorotate->GetRotate().x < 0)
	{
		rotationxval += 360;
	}




	parttorotate->SetRotate(Vector3(rotationxval, rotationval, 0));


}

void NPC::RotateToVector(GameObject* parttorotate, Vector3 rotate)
{
	//Vector3 point = GetTranslate() + Vector3(0, 1.8, 1);
	Vector3 AxisDir(0, 0, 1);


	//Vector3 objectdiff = (point - (GetTranslate() + Vector3(0, 1.8, 0))).Normalized();

	Vector3 objectdiff = Vector3(0, 0, 1).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(rotate.x, 1, 0, 0);
	objectdiff = rotation * objectdiff;
	rotation.SetToRotation(rotate.y, 0, 1, 0);
	objectdiff = rotation * objectdiff;
	rotation.SetToRotation(rotate.z, 0, 0, 1);
	objectdiff = rotation * objectdiff;


	float currentAngle = parttorotate->GetRotate().y;
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
	rotationval = (1 - ROTATIONSPEED) * parttorotate->GetRotate().y + ROTATIONSPEED * currentAngle;
	if (parttorotate->GetRotate().y > 360)
	{
		rotationval -= 360;
	}
	else if (parttorotate->GetRotate().y < 0)
	{
		rotationval += 360;
	}



	AxisDir = Vector3(0, 0, 1);
	currentAngle = parttorotate->GetRotate().x;
	temp.SetToRotation(-rotationval, 0, 1, 0);
	AxisDir = temp * AxisDir;

	


	objectdiff = temp * objectdiff;
	temp.SetToRotation(-(GetRotate().y), 0, 1, 0);
	temp.SetToRotation(Math::RadianToDegree(atan2(objectdiff.y, abs(objectdiff.z))), 1, 0, 0);
	AxisDir = temp * AxisDir;
	float targetpitch = Math::RadianToDegree(atan2(AxisDir.y, AxisDir.z));
	if (targetpitch < 0)
		targetpitch += 360;

	


	float smallestpitch = 999.f;
	for (int i = -1; i <= 1; ++i)
	{
		float thispitch = targetpitch + i * 360.f;
		if (fabs(thispitch - currentAngle) < fabs(smallestpitch - currentAngle))
		{
			smallestpitch = thispitch;
		}
	}
	currentAngle = smallestpitch;

	float rotationxval;
	rotationxval = (1 - ROTATIONSPEED) * parttorotate->GetRotate().x + ROTATIONSPEED * currentAngle;
	if (parttorotate->GetRotate().x > 360)
	{
		rotationxval -= 360;
	}
	else if (parttorotate->GetRotate().x < 0)
	{
		rotationxval += 360;
	}




	parttorotate->SetRotate(Vector3(rotationxval, rotationval, 0));

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



void NPC::LerpToPos(Vector3 pos, float speed)
{
	float distspeed = speed * dt;
	Vector3 curr = GetTranslate();
	float lerpx = lerp(curr.x, pos.x, distspeed);
	float lerpy = lerp(curr.y, pos.y, distspeed);
	float lerpz = lerp(curr.z, pos.z, distspeed);
	SetTranslate(Vector3(lerpx, lerpy, lerpz));
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

float lerp(float a, float b, float t) {
	return a + t * (b - a);
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

	
	if (cosine < 0 ) {
		angle = 180 + angle;
	}



	return -angle;
}