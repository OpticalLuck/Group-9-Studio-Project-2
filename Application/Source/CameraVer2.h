#pragma once
#include "Vector3.h"

class CameraVer2
{
public:
	enum CAMERA_MODE
	{
		FIRST_PERSON,
		THIRD_PERSON,
		FREE_VIEW,
		ANIMATION,
		TOTAL
	};
	CameraVer2();
	~CameraVer2();
	void Init(Vector3 position = Vector3(0, 3, 8), const Vector3& view = Vector3(1, 0, 0), const Vector3& up = Vector3(0, 1, 0));
	void Update(double x_offset, double y_offset);
	void Updatemovement(double dt);
	void SetTarget(Vector3 target);
	void SetPosition(Vector3 position);
	void SetView(Vector3 view);
	void Jump(double dt);
	void ToggleMode(CAMERA_MODE mode);
	void ToggleAnimation(float distance);
	void ToggleControls(bool Controls);

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
	
private:
	Vector3 position;
	Vector3 view;
	Vector3 up;
	Vector3 target;
	CAMERA_MODE mode, prev_mode;
	float sensitivity, speed, distance;
	bool IsKeyPressed, IsJump, IsGround, Controls;
};

