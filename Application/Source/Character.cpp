#include "Character.h"
#include "Application.h"
#include <cmath>

int Character::collectibleCount = 0;
Character::Character(unsigned int ID, Mesh* mesh):
	VertVelocity(0)
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
	speedModifier = 5.0f;

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
}

void Character::Update(CameraVer2* camera, double dt)
{
	//You dont need to redo the camera calculations, just change the translate and the camera does it's own shit
	float SPEED = speedModifier * dt;

	//Jump code
	{
		float gravity = -20.f;
		float jumpSpeed = 3.f;

		if (GetTranslate().y < Math::EPSILON) {
			SetTranslate(Vector3(GetTranslate().x, 0, GetTranslate().z));
			isGrounded = true;
		}

		if (isGrounded && VertVelocity < 0) {
			VertVelocity = 0;
		}
		if (Application::IsKeyPressed(VK_SPACE) && isGrounded)
		{
			isJump = true;
			isGrounded = false;
			VertVelocity = std::sqrt(jumpSpeed * -2 * gravity);
		}
		else if (Application::IsKeyPressed(VK_SPACE) && isJump && VertVelocity < 0)
		{
			gravity = -0.5f;
			SPEED *= 1.5;
		}

		VertVelocity += gravity * dt;

		SetTranslate(GetTranslate() + Vector3(0, 1, 0) * VertVelocity * dt);
	}

	//USED FOR DIRECTION
	//Direction the character is going towards aka direction vector
	Vector3 Direction(0,0,0);
	//Get camera front and right without the Y coordinate so dont have to copy paste
	Vector3 camFront(camera->GetView().x, 0, camera->GetView().z);
	Vector3 camRight(camera->GetRight().x, 0, camera->GetRight().z);

	//USED FOR ROTATION
	float ROTATIONSPEED = 8 * dt;
	Vector3 AxisDir(0, 0, 0);// Direction vector along the axis for calculating rotation
	bool KeyPressed = false;
	float CharAngle = GetRotate().y;

	if (Application::IsKeyPressed('W')) 
	{
		Direction += camFront;
		AxisDir += Vector3(0, 0, 1);
		KeyPressed = true;
	}
	if (Application::IsKeyPressed('A')) 
	{
		Direction -= camRight;
		AxisDir += Vector3(1, 0, 0);
		KeyPressed = true;
	}
	if (Application::IsKeyPressed('S')) 
	{
		Direction -= camFront;
		AxisDir += Vector3(0, 0, -1);
		KeyPressed = true;
	}
	if (Application::IsKeyPressed('D')) 
	{
		Direction += camRight;
		AxisDir += Vector3(-1, 0, 0);
		KeyPressed = true;
	}

	if (Application::IsKeyPressed(VK_LSHIFT) && isSprintable == true)
	{
		speedModifier = 10.0f;
	}
	else
	{
		speedModifier = 5.0f;
	}
	
	if (!Direction.IsZero())
	{
		Direction.Normalize();
	}
	SetTranslate(GetTranslate() + SPEED * Direction);

	Mtx44 temp;
	temp.SetToRotation(Math::RadianToDegree(atan2(camera->GetView().x, camera->GetView().z)), 0, 1, 0);
	AxisDir = temp * AxisDir;

	if (KeyPressed)
	{
		float targetyaw = Math::RadianToDegree(atan2(AxisDir.x, AxisDir.z)); // + camera->GetYaw();
		if (targetyaw < 0)
			targetyaw += 360;

		float smallestyaw = 999.f;
		for (int i = -1; i <= 1; ++i)
		{
			float thisyaw = targetyaw + i * 360.f;
			if (fabs(thisyaw - CharAngle) < fabs(smallestyaw - CharAngle))
			{
				smallestyaw = thisyaw;
			}
		}
		CharAngle = smallestyaw;
	}

	//Rotation for character
	float rotationval;
	rotationval = (1 - ROTATIONSPEED) * GetRotate().y + ROTATIONSPEED * CharAngle;
	//Range reset for mouse rotation
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




bool Character::IsWithinRangeOf(GameObject* item)
{
	//getTranslate() by itself access the position of Character, while item->GetTranslate() access the position of the item parameter that is passed in
	if (GetInRange(item,item->GetRadius()))
	{
		item->SetCurrentFlag(FLAG1);
		return true;
	}
	item->SetCurrentFlag(FLAG0);
	return false;
}

int Character::getCollectibleCount()
{
	return collectibleCount;
}

bool Character::getSprintState()
{
	return isSprintable;
}

void Character::setSprintState(bool sprintable)
{
	this->isSprintable = sprintable;
}

void Character::IncrementCollectible()
{
	collectibleCount += 1;
}





//void Character::SetCamera(CameraVer2* camera)
//{
//	this->camera = camera;
//}
