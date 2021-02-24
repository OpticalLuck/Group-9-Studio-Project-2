#include "CameraVer2.h"
#include "Mtx44.h"
#include "Application.h"

CameraVer2::CameraVer2():
	target(nullptr),
	mode(FIRST_PERSON),
	sensitivity(0.05f),
	speed(5.f),
	distance(8.f),
	IsKeyPressed(false),
	IsJump(false),
	IsGround(true),
	Controls(true),
	IsSprintable(false),
	yaw(0)
{
}

CameraVer2::~CameraVer2()
{
}

void CameraVer2::Init(Vector3 position, const Vector3& view, const Vector3& up)
{
	this->position = position;
	this->view = view.Normalized();
	this->up = up.Normalized();
}

void CameraVer2::Update(double x_offset, double y_offset)
{
	yaw -= x_offset * 0.05f;
	if (yaw > 360)
		yaw -= 360;
	if (yaw < -360)
		yaw += 360;

	// When controls
	if (Controls)
	{
		Mtx44 RotateYaw;
		RotateYaw.SetToRotation(-x_offset * sensitivity, 0, 1, 0);
		view = RotateYaw * view;

		float AvailableUP = Math::RadianToDegree(acosf(view.Dot(up))) -0.5 ;
		float AvailableDOWN = Math::RadianToDegree(acosf(view.Dot(-up))) -0.5;
	
		float Angle = y_offset * sensitivity;
		//Clamps angle to maximum AvailableDOWN/UP
		Angle = Math::Clamp(Angle, -AvailableDOWN, AvailableUP);

		Mtx44 RotatePitch;
		Vector3 right = GetRight();
		RotatePitch.SetToRotation(Angle, right.x, right.y, right.z);
		view = RotatePitch * view;

		if (mode == THIRD_PERSON && target)
		{
			//reverses first person camera
			position = target->GetTranslate() + distance * -view;
		}
	}
}

void CameraVer2::Updatemovement(double dt)
{
	if (Controls)
	{
		if (mode != THIRD_PERSON)
		{
			Vector3 direction = Vector3(view.x, 0, view.z).Normalized();
			if (Application::IsKeyPressed('W'))
			{
				if(mode == FREE_VIEW)
				{
					position += view * dt * speed;
				}

				position.x += direction.x * dt * speed;
				position.z += direction.z * dt * speed;
			}
			if (Application::IsKeyPressed('S'))
			{
				if (mode == FREE_VIEW)
				{
					position -= view * dt * speed;
				}
				else
				{
					position.x -= direction.x * dt * speed;
					position.z -= direction.z * dt * speed;
				}
			}
			if (Application::IsKeyPressed('A'))
			{
				position -= GetRight() * dt * speed;
			}
			if (Application::IsKeyPressed('D'))
			{
				position += GetRight() * dt * speed;
			}
		

			if (Application::IsKeyPressed(VK_LSHIFT) && IsSprintable == true)
			{
				speed = 10.0f;
			}
			else
			{
				speed = 5.0f;
			}

			if (mode == FREE_VIEW) {
				if (Application::IsKeyPressed(VK_SPACE)) {
					position += GetUp() * dt * speed;
				}
				if (Application::IsKeyPressed(VK_LCONTROL)) {
					position -= GetUp() * dt * speed;
				}
			}
			else {
				if (Application::IsKeyPressed(VK_SPACE) && !IsKeyPressed)
				{
					IsKeyPressed = true;
					if (IsGround)
					{
						IsJump = true;
					}
				}
				else if (!Application::IsKeyPressed(VK_SPACE) && IsKeyPressed)
				{
					IsKeyPressed = false;
				}

				Jump(dt);

				position.x = Math::Clamp(position.x, -30.f, 30.f);
				position.y = Math::Clamp(position.y, 3.f, 5.f);
				position.z = Math::Clamp(position.z, -30.f, 30.f);
			}
		}
		else
		{
			float SPEED = target->getVelocity() * dt;
			Vector3 Height(0, 3, 0);
			//Jump code
			{
				float gravity = -20.f;
				float jumpSpeed = 3.f;

				if (target->GetTranslate().y < Math::EPSILON) {
					target->SetTranslate(Vector3(target->GetTranslate().x, 0, target->GetTranslate().z));
					target->setbGrounded(true);
				}

				if (target->getbGrounded() && target->getVertVelocity() < 0) 
				{
					target->setVertVelocity(0);
				}
				if (Application::IsKeyPressed(VK_SPACE) && target->getbGrounded())
				{
					target->setbjump(true);
					target->setbGrounded(false);
					target->setVertVelocity(std::sqrt(jumpSpeed * -2 * gravity));
				}
				else if (Application::IsKeyPressed(VK_SPACE) && target->getbJump() && target->getVertVelocity() < 0)
				{
					gravity = -0.5f;
					SPEED *= 1.5;
				}

				target->setVertVelocity(target->getVertVelocity() + gravity * dt);
				target->SetTranslate(target->GetTranslate() + Vector3(0, 1, 0) * target->getVertVelocity() * dt);
			}

			//USED FOR DIRECTION
			//Direction the character is going towards aka direction vector
			Vector3 Direction(0, 0, 0);
			//Get camera front and right without the Y coordinate so dont have to copy paste
			Vector3 camFront(view.x, 0, view.z);
			Vector3 camRight(GetRight().x, 0, GetRight().z);

			//USED FOR ROTATION
			float ROTATIONSPEED = 8 * dt;
			Vector3 AxisDir(0, 0, 0);// Direction vector along the axis for calculating rotation
			bool KeyPressed = false;
			float CharAngle = target->GetRotate().y;

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

			if (Application::IsKeyPressed(VK_LSHIFT) && target->getSprintState())
			{
				target->setVelocity(10.f) ;
			}
			else
			{
				target->setVelocity(5.f);
			}

			if (!Direction.IsZero())
			{
				Direction.Normalize();
			}
			target->SetTranslate(target->GetTranslate() + SPEED * Direction);

			Mtx44 temp;
			temp.SetToRotation(Math::RadianToDegree(atan2(view.x, view.z)), 0, 1, 0);
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
			rotationval = (1 - ROTATIONSPEED) * target->GetRotate().y + ROTATIONSPEED * CharAngle;
			//Range reset for mouse rotation
			if (target->GetRotate().y > 360)
			{
				rotationval -= 360;
			}
			else if (target->GetRotate().y < 0)
			{
				rotationval += 360;
			}

			target->SetRotate(Vector3(0, rotationval, 0));

			position = target->GetTranslate() + distance * -view + Height;
		}
	}
}

void CameraVer2::Updateposition()
{
	position = target->GetTranslate() + distance * -view + Vector3(0,3,0);
}

void CameraVer2::SetPosition(Vector3 position)
{
	this->position = position;
}

void CameraVer2::SetView(Vector3 view)
{
	this->view = view.Normalized();
}

void CameraVer2::SetSprintState(bool sprintable)
{
	this->IsSprintable = sprintable;
}

void CameraVer2::Jump(double dt)
{
	float JumpSpeed = 5.0f;
	if (mode == THIRD_PERSON)
	{
		if (IsJump)
		{
			IsGround = false;
			if (target->GetTranslate().y < 5.f)
			{
				
				target->SetTranslate(target->GetTranslate() + Vector3(0, JumpSpeed * dt, 0));
			}
			else
			{
				IsJump = false;
			}
		}
		else
		{
			if (target->GetTranslate().y > 3.f)
			{
				target->SetTranslate(target->GetTranslate() - Vector3(0, JumpSpeed * dt, 0));
			}
			else
			{
				IsGround = true;
			}
		}
	}
	else
	{
		if (IsJump)
		{
			IsGround = false;
			if (position.y < 5.f)
			{

				position.y += JumpSpeed * dt;
			}
			else
			{
				IsJump = false;
			}
		}
		else
		{
			if (position.y > 3.f)
			{
				position.y -= JumpSpeed * dt;
			}
			else
			{
				IsGround = true;
			}
		}
	}
}

void CameraVer2::ToggleMode(CAMERA_MODE mode)
{
	prev_mode = this->mode;
	this->mode = mode;
}

void CameraVer2::ToggleAnimation(float distance)
{
	float WatchingDist = 8.f;
	if (mode != ANIMATION)
	{

		if (mode == THIRD_PERSON)
		{
			//position = target;
		}
		Controls = false;
		prev_mode = mode;
		mode = ANIMATION;

		position += WatchingDist * GetRight() + (distance * 0.5f) * view.Normalized();
		view = (GetRight() * -1).Normalized();
	}
	else
	{
		view = GetRight();
		Controls = true;
		mode = prev_mode;
	}
}

void CameraVer2::ToggleControls(bool Controls)
{
	this->Controls= Controls;
}

void CameraVer2::SetYaw(float yaw)
{
	this->yaw = yaw;
}

void CameraVer2::SetTarget(Character* character)
{
	target = character;
}

Vector3 CameraVer2::GetRight() const
{
	return view.Cross(up).Normalized();
}

float CameraVer2::GetYaw() const
{
	//return Math::RadianToDegree(atan2(view.z,view.x));.
	return yaw;
}

float CameraVer2::GetPitch() const
{
	return Math::RadianToDegree(acosf(view.Dot(up))) - 90;
}

const Vector3 CameraVer2::GetObjPos()
{
	if (mode == THIRD_PERSON)
	{
		return position + view * distance;
	}
	else
	{
		return position;
	}
}



const Vector3& CameraVer2::GetPosition()
{
	// TODO: insert return statement here
	return position;
}

const Vector3& CameraVer2::GetView()
{
	// TODO: insert return statement here
	return view;
}

const Vector3& CameraVer2::GetUp()
{
	// TODO: insert return statement here
	return up;
}

const CameraVer2::CAMERA_MODE& CameraVer2::GetPrevMode()
{
	// TODO: insert return statement here
	return prev_mode;
}

const CameraVer2::CAMERA_MODE& CameraVer2::GetMode()
{
	// TODO: insert return statement here
	return mode;
}

std::string CameraVer2::GetStrMode() const
{
	switch (mode)
	{
	case FIRST_PERSON:
		return "First Person";
	case THIRD_PERSON:
		return "Third Person";
	case FREE_VIEW:
		return "Free View";
	case ANIMATION:
		return "Animation";
	};
}

const bool CameraVer2::GetSprintState()
{
	return IsSprintable;
}

const float CameraVer2::GetSpeed()
{
	return speed;
}

const float CameraVer2::GetPosX()
{
	return position.x;
}

const float CameraVer2::GetPosZ()
{
	return position.z;
}