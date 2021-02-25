#include "Character.h"
#include "Application.h"
#include <cmath>

int Character::collectibleCount = 0;
Character::Character(unsigned int ID, Mesh* mesh):
	VertVelocity(0),
	Velocity(0)
{
	SetID(ID);
	SetMesh(mesh);
	//camera = NULL;
}

Character::~Character()
{
}

void Character::Init(Vector3 position, Vector3 rotation, Vector3 scale)
{
	isSprintable = false;
	Velocity = 5.0f;

	SetTranslate(position);
	SetRotate(rotation);
	SetScale(scale);
	//collectibleCount = 0;

	if (position.y < Math::EPSILON)
	{
		isJump = false;
		isGrounded = true;
	}
	else
	{
		isJump = true;
		isGrounded = false;
	}

	SetColliderBox(Vector3(0.3, 0.1, 0.3), Vector3(0, 0.1, 0)); //foot box (always first)

}

void Character::Update(double dt)
{
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
}

int Character::getCollectibleCount()
{
	return collectibleCount;
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

float Character::getVertVelocity()
{
	return VertVelocity;
}

float Character::getVelocity()
{
	return Velocity;
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

void Character::setbjump(bool isJump)
{
	this->isJump = isJump;
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

}







//void Character::SetCamera(CameraVer2* camera)
//{
//	this->camera = camera;
//}
