#include "Train.h"

Train::Train(unsigned int id, Mesh* mesh) 
{
	SetMesh(mesh);
	SetID(id);
	SetRadius(10.f);
	SetCurrentFlag(FLAG0);
	objectToLookAt = NULL;
	door = NULL;

	collisionboxes = NULL;

	velocity = 0;
	nextstop = nextstation = 0;
	dt = 0;
	externalCollider = 0;
}

Train::~Train()
{
	delete door;
	delete collisionboxes;
}

void Train::Update(double dt)
{
	this->dt = dt;
	Vector3 playerpos = objectToLookAt->GetTranslate();

	if (getCurrentFlag() == FLAG2) 
	{ //close the doors
		if (door->GetTranslate().x < 1.0) 
		{
			door->SetTranslate(Vector3(door->GetTranslate().x + 2 * dt, 0.2, 2.4));
		}
		else if (door->GetTranslate().x >= 1.0) 
		{
			door->SetTranslate(Vector3(1.0, 0.2, 2.4)); //Keep at this position
			SetCurrentFlag(FLAG3); //Start moving train

		}
		
		if (!externalCollider)
			SetCurrentFlag(FLAG4);

	}
	else if (getCurrentFlag() == FLAG3 && !stops.empty() && nextstop < static_cast<int>(stops.size())) 
	{ //train movement
		float speed = 10.f * dt;

		if (stops.back() != station.back()) 
		{ //if last station not set
			station.push_back(stops.back());
		}

		if (!station.empty() && stops.at(nextstop) == station.front()) 
		{ //slow down when nearing station
			velocity -= speed;
			
		}
		else 
		{
			velocity += speed;
		}

		velocity = Math::Clamp(velocity, 3.f, 20.f);

		MoveToPos(stops.at(nextstop), velocity);

		RotateToObject(stops.at(nextstop)); //rotate to next stop

		Vector3 velocitydir = (stops.at(nextstop) - GetTranslate()).Normalized();
		if (externalCollider) //if player in externalCollider
			objectToLookAt->SetTranslate(playerpos + velocitydir * velocity * dt); //move with train
		

		if (abs((GetTranslate() - stops.at(nextstop)).Length()) < 1) 
		{
			if (stops.at(nextstop) == station.at(nextstation)) 
			{
				SetCurrentFlag(FLAG4);
				nextstation++;
			}
			nextstop++;

		}

	}
	else if (getCurrentFlag() == FLAG4) 
	{
		
		if (door->GetTranslate().x > -1.8) 
		{
			door->SetTranslate(Vector3(door->GetTranslate().x - 2 * dt, 0.2, 2.4));
			//GetColliderBox(1)->setOffsetpos(door->GetTranslate() + Vector3(0, 1, 0));
		}
		else if (door->GetTranslate().x <= -1.8) 
		{
			door->SetTranslate(Vector3(-1.8, 0.2, 2.4));
			SetCurrentFlag(FLAG5); //undo door

		}

	}
	else if (getCurrentFlag() == FLAG5) 
	{
		if (!externalCollider) 
		{
			SetCurrentFlag(FLAG0);

			if (nextstop >= getStopLen() && nextstation >= getStationLen())
				nextstop = nextstation = velocity = 0;
		}
	}
	else if (externalCollider)
	{
		SetCurrentFlag(FLAG2);
	}
}

void Train::Init(MeshList* meshlist, GameObject* lookedAtObj)
{
	BuildMeshes(meshlist);
	objectToLookAt = lookedAtObj;
}

Train* Train::PushStop(Vector3 dest)
{
	stops.push_back(dest);
	return this;
}

Train* Train::PushStop(float x, float y, float z)
{
	return PushStop(Vector3(x, y, z));
}

Train* Train::ExtendStop(Vector3 dest)
{

	return PushStop(stops.back() + dest);
}

Train* Train::ExtendStop(float x, float y, float z)
{
	return ExtendStop( Vector3(x,y,z) );
}

void Train::SetStation()
{
	station.push_back(stops.back());
}

void Train::SetTransparentCollider(bool collision)
{
	externalCollider = collision;
}





void Train::BuildMeshes(MeshList* meshlist)
{
	Vector3 cool; //for debugging

	SetColliderBox(Vector3(4.5, 0.1, 3)); 
	
	
	door = new GameObject(GetID(), meshlist->GetMesh(MeshList::MESH_TRAINDOOR));
	door->SetTranslate(Vector3(-1.8, 0.2, 2.4));
	this->AddChild(door);
	door->SetColliderBox(Vector3(1.75, 1.25, 0) , Vector3(0,1,0)); //, door->GetTranslate() + Vector3(0,1,0)); 
	//door collider (idx 1)
	
	SetColliderBox(Vector3(2, 1.2, 0.2), Vector3(-2.45, 1, 2.7));

	SetColliderBox(Vector3(0.9, 1.2, 0.2), Vector3(3.5, 1, 2.7));

	SetColliderBox(Vector3(0.2, 1.2, 2.1), Vector3(4.5, 1, 0));
	SetColliderBox(Vector3(0.2, 1.2, 2.1), Vector3(-4.5, 1, 0));

	SetColliderBox(Vector3(4.5, 1.2, 0.2), Vector3(0, 1, -2.7));

}

void Train::RotateToObject(Vector3 point)
{
	float rotateofTrain = GetRotate().y + 90;

	Vector3 AxisDir(0, 0, 1);

	Vector3 objectdiff = (point - GetTranslate()).Normalized();
	float currentAngle = GetRotate().y + 90;
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


	float angleToPoint = GetAngleToPoint(stops.at(nextstop));
	float offsetangle = 0.9f;
	float ROTATIONSPEED = 11 * dt;
	float rotationval;

	rotationval = (1 - ROTATIONSPEED) * rotateofTrain + ROTATIONSPEED * angleToPoint;
	if (rotateofTrain > 360)
	{
		rotationval -= 360;
	}
	else if (rotateofTrain < 0)
	{
		rotationval += 360;
	}
	SetRotate(Vector3(0, rotationval - 90, 0));

}

int Train::getStationLen()
{
	return static_cast<int>(station.size()) ;
}

int Train::getStopLen()
{
	return static_cast<int>(stops.size());
}
