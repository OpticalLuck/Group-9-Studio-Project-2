#include "GameObject.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

GameObject::GameObject() :
	mesh(nullptr),
	Pos(Vector3(0, 0, 0)),
	Translation(Vector3(0, 0, 0)),
	Scale(Vector3(1, 1, 1)),
	Rotation(Vector3(0, 0, 0)),
	PivotRotate(Vector3(0, 0, 0)),
	Interacted(false),
	Active(true),
	tracking(true),
	IsDead(false),
	Parent(nullptr)
{
}

GameObject::GameObject(Vector3 Position, Mesh* mesh) :
	mesh(nullptr),
	Pos(Vector3(0, 0, 0)),
	Translation(Vector3(0, 0, 0)),
	Scale(Vector3(1, 1, 1)),
	Rotation(Vector3(0, 0, 0)),
	PivotRotate(Vector3(0, 0, 0)),
	Interacted(false),
	Active(true),
	tracking(true),
	IsDead(false),
	Parent(nullptr)
{
	Pos = Position;
	this->mesh = mesh;
}

GameObject::~GameObject()
{
}

void GameObject::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void GameObject::SetTexture(std::string TextureID)
{
	mesh->textureID = LoadTGA(TextureID.c_str());
}

void GameObject::SetPos(Vector3 Pos)
{
	this->Pos = Pos;
}

void GameObject::SetTranslate(Vector3 Translate)
{
	Translation = Translate;
}

void GameObject::SetRotate(Vector3 Rotate)
{
	Rotation = Rotate;
}

void GameObject::SetScale(Vector3 Scale)
{
	this->Scale = Scale;
}

void GameObject::SetPRotate(Vector3 PivotRotate)
{
	this->PivotRotate = PivotRotate;
}

void GameObject::SetInteracted(bool state)
{

	Interacted = state;
	
}

void GameObject::SetActive(bool Active)
{
	this->Active = Active;
}

void GameObject::bTracking(bool tracking)
{
	this->tracking = tracking;
}

void GameObject::SetTarget(GameObject* target)
{
	Vector3 ObjToTarget = GetPos() - target->GetPos();
	float angle;
	angle = Math::RadianToDegree(atan2(ObjToTarget.z, ObjToTarget.x));

	if (tracking)
	{
		SetRotate(Vector3(0 ,270 - angle , 0));
	}
}

void GameObject::Draw(Renderer* renderer, bool EnableLight)
{
	renderer->PushTransform();
	//scale, translate, rotate
	renderer->AddTransformation(Translation, Pos, Rotation, Scale, PivotRotate);
	if (Active)
	{
		renderer->RenderMesh(mesh, EnableLight);
	}

	//future can add child thing for hierchical stuff pain
	for (int i = 0; i < Child.size(); i++)
	{
		if (GetChild(i))
		{
			Child.at(i)->Draw(renderer, true);
		}
	}
	renderer->PopTransform();
}

void GameObject::AddChild(GameObject* GO)
{
	GO->Parent = this;
	Child.push_back(GO);
}

void GameObject::SetIsDead(bool IsDead)
{
	this->IsDead = IsDead;
}

Mesh* GameObject::GetMesh()
{
	return mesh;
}

Vector3 GameObject::GetPos()
{
	return Pos+Translation;
}

Vector3 GameObject::GetTranslate()
{
	return Translation;
}

Vector3 GameObject::GetRotate()
{
	return Rotation;
}

Vector3 GameObject::GetScale()
{
	return Scale;
}

Vector3 GameObject::GetPRotate()
{
	return PivotRotate;
}

GameObject* GameObject::GetChild(int idx)
{
	return Child.at(idx);
}

bool GameObject::inRange(GameObject* targetObj, float Range)
{
	if (abs((targetObj->Pos - Pos).Length()) < Range)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameObject::getInteracted()
{
	return Interacted;
}

bool GameObject::getActive()
{
	return Active;
}

bool GameObject::getIsDead()
{
	return IsDead;
}



