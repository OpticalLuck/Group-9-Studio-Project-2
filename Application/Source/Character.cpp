#include "Character.h"
#include "Application.h"
#include "MeshList.h"
#include <cmath>

int Character::collectibleCount = 0;
Character::Character(unsigned int ID, Mesh* mesh):
	VertVelocity(0),
	Velocity(0),
	Stamina(100),
	canGlide(false)
{
	SetID(ID);
	SetMesh(mesh);
	Wing = new GameObject(ID, MeshList::GetInstance()->GetMesh(MeshList::MESH_WING));
	Wing->SetTranslate(Vector3(0, 3.2f, -0.4f));
	Wing->SetScale(Vector3(0.05f, 0.05f, 0.05f));
	Wing->SetActive(false);

	AddChild(Wing);
}

Character::~Character()
{
}

void Character::Init(Vector3 position, Vector3 rotation, Vector3 scale)
{
	isSprintable = false;
	isGliding = false;
	isJump = false;
	Velocity = 5.0f;

	SetTranslate(position);
	SetRotate(rotation);
	SetScale(scale);
	//collectibleCount = 0;

	if (position.y < Math::EPSILON)
	{
		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}

	SetColliderBox(Vector3(0.6, 0.1, 0.6), Vector3(0, 0.1, 0)); //foot box (always first)
}

void Character::Update(double dt)
{
	if (Wing->getActive())
	{
		float ScaleFactor = Wing->GetScale().x;
		float expandingspeed = 20 * dt;
		float finalscale = (1 - expandingspeed)* ScaleFactor + expandingspeed * 1;

		Wing->SetScale(Vector3(finalscale, finalscale, finalscale));

	}
	else
	{
		Wing->SetScale(Vector3(0.05f, 0.05, 0.05f));
	}

	UpdateCollision();
}

bool Character::IsWithinRangeOf(GameObject* item)
{
	//getTranslate() by itself access the position of Character, while item->GetTranslate() access the position of the item parameter that is passed in
	if (GetInRange(item,item->GetRadius()) && item->getCurrentFlag() == FLAG0)
	{
		item->SetCurrentFlag(FLAG1);
		return true;
	}
	else if (item->getCurrentFlag() == FLAG1 && !GetInRange(item, item->GetRadius())) {
		item->SetCurrentFlag(FLAG0);
		return false;
	}
	else
	{
		return false;
	}
}

int Character::getCollectibleCount()
{
	return collectibleCount;
}

int Character::getRingCount()
{
	return ringCount;
}

bool Character::getSprintState()
{
	return isSprintable;
}

bool Character::getbGrounded()
{
	return isGrounded;
}

bool Character::getbJump()
{
	return isJump;
}

bool Character::getbGlide()
{
	return isGliding;
}

bool Character::getcanGlide()
{
	return canGlide;
}

float Character::getVertVelocity()
{
	return VertVelocity;
}

float Character::getVelocity()
{
	return Velocity;
}

float Character::getStamina()
{
	return Stamina;
}

GameObject* Character::getWing()
{
	return Wing;
}

void Character::setSprintState(bool sprintable)
{
	this->isSprintable = sprintable;
}

void Character::setbGrounded(bool isGrounded)
{
	this->isGrounded = isGrounded;
}

void Character::setVertVelocity(float VertVelocity)
{
	this->VertVelocity = VertVelocity;
}

void Character::setVelocity(float Velocity)
{
	this->Velocity = Velocity;
}

void Character::setStamina(float stamina)
{
	Stamina = stamina;
	if (Stamina <= 0)
	{
		Stamina = 0;
	}
	else if (Stamina > 100)
	{
		Stamina = 100;
	}
}

void Character::setbjump(bool isJump)
{
	this->isJump = isJump;
}

void Character::setbGlide(bool isGliding)
{
	this->isGliding = isGliding;

	if (isGliding)
	{
		Wing->SetActive(true);
	}
	else
	{
		Wing->SetActive(false);
	}
}

void Character::setRingCount(int ringCount)
{
	this->ringCount = ringCount;
}

void Character::setcanGlide(bool canGlide)
{
	this->canGlide = canGlide;
}

void Character::IncrementCollectible()
{
	collectibleCount += 1;
}

void Character::CollisionResolution(GameObject* target)
{
	for (int i = 0; i < GetCollVecSize(); i++)
	{
		for (int j = 0; j < target->GetCollVecSize(); j++)
		{
			Info CollisionInfo = GetColliderBox(i)->CheckOBBCollision(target->GetColliderBox(j));
			
			//Standing on checking
			if (target->GetColliderBox(j) == objectStoodOn && i == 0) {
				isGrounded = CollisionInfo.Collided;
				if (!isGrounded) {
					objectStoodOn = NULL;
					
				}
			}

			if (CollisionInfo.Collided)
			{
				Collision* objBox = GetColliderBox(i);
				Collision* targetBox = target->GetColliderBox(j);
				float distance = CollisionInfo.distance;
				if ((objBox->GetPos() - targetBox->GetPos()).Dot(CollisionInfo.Axis) < 0)
				{
					distance = distance * -1;
				}
				Vector3 Translation = GetTranslate();
				Translation += distance * CollisionInfo.Axis;
				SetTranslate(Translation);
				for (int updateidx = 0; updateidx < GetCollVecSize(); updateidx++)
					GetColliderBox(updateidx)->setTranslate(Translation);

				if (i == 0 && objectStoodOn == NULL) 
				{
						objectStoodOn = target->GetColliderBox(j);
				}

			}
			
		}
	}

	if (target->GetNoOfChild() > 0)
	{
		for (int idx = 0; idx < target->GetNoOfChild(); idx++)
		{
			CollisionResolution(target->GetChild(idx));
		}
	}
}







//void Character::SetCamera(CameraVer2* camera)
//{
//	this->camera = camera;
//}
