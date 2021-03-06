#pragma once
#include "Vector3.h"
#include "Character.h"

class CameraVer2
{
public:
	enum CAMERA_MODE
	{
		FIRST_PERSON,
		THIRD_PERSON,
		FREE_VIEW,
		CHARACTER_CONTROLLED,
		ANIMATION,
		TOTAL
	};
	CameraVer2();
	~CameraVer2();
	//Initialises position, view, up only
	void Init(Vector3 position = Vector3(0, 3, 8), const Vector3& view = Vector3(1, 0, 0), const Vector3& up = Vector3(0, 1, 0));
	//Updates the view angles
	//x_offset for left and right, y_offset for up and down
	void Update(double x_offset, double y_offset);
	//Updates view based on input
	void Updatemovement(double dt);
	void Updateposition();

	void SetPosition(Vector3 position);
	void SetView(Vector3 view);
	void SetClamp(Vector3 clampVal);
	void SetSprintState(bool sprintable);
	
	//Camera jumps
	void Jump(double dt);
	//SETS MODE TO ONE OF THESE MODES : FIRST_PERSON, THIRD_PERSON, FREE_VIEW, ANIMATION
	void ToggleMode(CAMERA_MODE mode);
	//toggles animation. param distance is distance between camera and object
	void ToggleAnimation(float distance);
	//Enables or Disables the ability to control the camera
	void ToggleControls(bool Controls);

	void SetYaw(float yaw);
	void SetTarget(Character* character);

	//getters
	Vector3 GetRight() const;
	float GetYaw() const;
	float GetPitch() const;
	const Vector3 GetObjPos();
	const Vector3& GetPosition();
	const Vector3& GetView();
	const Vector3& GetUp();
	const CAMERA_MODE& GetPrevMode();
	const CAMERA_MODE& GetMode();
	std::string GetStrMode() const;

	const bool GetSprintState();
	const float GetSpeed();
	const float GetPosX();
	const float GetPosZ();
	
private:
	Vector3 position;
	Vector3 view;
	Vector3 up;
	Vector3 clampVal;
	Character* target;
	CAMERA_MODE mode, prev_mode;
	float sensitivity, camspeed, distance, pos_x, pos_z; //for fps 

	//for third person
	float yaw;
	float gravity, jumpSpeed;
	bool IsSpacePressed, IsJump, IsGround, Controls, IsSprintable;
};

