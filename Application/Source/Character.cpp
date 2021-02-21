#include "Character.h"
#include "Application.h"
#include <cmath>

int Character::collectibleCount = 0;
Character::Character(unsigned int ID, Mesh* mesh)
{
	SetID(ID);
	SetMesh(mesh);
	//camera = NULL;
	charspeed = 10.f;
	isGrounded = false;
	weight = 20.f;
	jumpVelocity = 3.f;
	groundPos = 0;
}

Character::~Character()
{
}

void Character::Init(Vector3 position, Vector3 rotation, Vector3 scale)
{
	SetTranslate(position);
	SetRotate(rotation);
	SetScale(scale);
	groundPos = position.y;
	//collectibleCount = 0;
}

void Character::Update(CameraVer2* camera, double dt)
{
	//You dont need to redo the camera calculations, just change the translate and the camera does it's own shit
	float SPEED = 5 * dt;

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
	float camAngle = GetRotate().y;

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
	//Set translate as its own + new direction
	//gravity
	//if (newpos.y < groundPos) {
	//	newpos.y = groundPos;
	//	isGrounded = true;
	//}
	//else {
	//	isGrounded = false;
	//}
	//if (isGrounded && VertVelocity.y < 0) {
	//	VertVelocity.y = 0;
	//}
	//
	//if (isGrounded && Application::IsKeyPressed(VK_SPACE)) {
	//	VertVelocity.y = std::sqrt(jumpVelocity * -2 * -weight);
	//}
	//std::cout << VertVelocity.y << "\n";
	//VertVelocity.y += -(weight * dt);
	//
	//newpos = newpos + VertVelocity * dt;
	//
	//SetTranslate(newpos);
	//
	//camera->SetPosition(newpos);
	//camera->SetTarget(view + newpos);

	if (!Direction.IsZero())
	{
		Direction.Normalize();
	}

	SetTranslate(GetTranslate() + SPEED * Direction);
	camera->SetTarget(GetTranslate() + Vector3(0,3.5f,0)); //Update Target Location for camera

	if (KeyPressed)
	{
		float anglemod = Math::RadianToDegree(atan2(AxisDir.x, AxisDir.z));
		camAngle = camera->GetYaw() + anglemod;
	}

	//Rotation for character
	float rotationval; // = (1 - ROTATIONSPEED) * GetRotate().y + ROTATIONSPEED * camAngle;
	float compare1 = fabs(GetRotate().y - camAngle);
	float compare2 = fabs(GetRotate().y - (camAngle - 360));
	float compare3 = fabs(GetRotate().y - (camAngle + 360));
	std::cout << compare1 << std::endl;
	std::cout << compare2 << std::endl;
	std::cout << compare3 << std::endl;
	if (compare1 > compare2)
	{
		camAngle -= 360;
		rotationval = (1 - ROTATIONSPEED) * GetRotate().y + ROTATIONSPEED * camAngle;
	}
	else
		rotationval = (1 - ROTATIONSPEED) * GetRotate().y + ROTATIONSPEED * camAngle;
	
	if (rotationval > 360) 
	{
		camera->SetYaw(camera->GetYaw() - 360);
		camAngle -= 360;
		rotationval -= 360;
	}
	else if (rotationval < -360)
	{
		camera->SetYaw(camera->GetYaw() + 360);
		camAngle += 360;
		rotationval += 360;
	}

	std::cout << "TARGET: " << camAngle << std::endl;
	std::cout << "-TARGET: " << camAngle - 360 << std::endl;
	std::cout << "ROTATING: " << rotationval << std::endl;
	system("CLS");
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

void Character::IncrementCollectible()
{
	collectibleCount += 1;
}

//void Character::SetCamera(CameraVer2* camera)
//{
//	this->camera = camera;
//}
