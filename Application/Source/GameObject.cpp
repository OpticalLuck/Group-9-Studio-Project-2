#include "GameObject.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

GameObject::GameObject() :
	mesh(nullptr),
	Translation(Vector3(0, 0, 0)),
	Scale(Vector3(1, 1, 1)),
	Rotation(Vector3(0, 0, 0)),
	isActive(true),
	isTracking(true),
	Parent(nullptr)
{
}

GameObject::GameObject(Mesh* mesh) :
	mesh(nullptr),
	Translation(Vector3(0, 0, 0)),
	Scale(Vector3(1, 1, 1)),
	Rotation(Vector3(0, 0, 0)),
	isActive(true),
	isTracking(true),
	Parent(nullptr)
{
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

void GameObject::SetActive(bool Active)
{
	this->isActive = Active;
}

void GameObject::bTracking(bool tracking)
{
	this->isTracking = tracking;
}

void GameObject::SetTarget(GameObject* target)
{
	Vector3 ObjToTarget = GetTranslate() - target->GetTranslate();
	float angle;
	angle = Math::RadianToDegree(atan2(ObjToTarget.z, ObjToTarget.x));

	if (isTracking)
	{
		SetRotate(Vector3(0 ,270 - angle , 0));
	}
}

void GameObject::Draw(Renderer* renderer, bool EnableLight)
{
	renderer->PushTransform();
	//scale, translate, rotate
	renderer->AddTransformation(Translation, Rotation, Scale);
	if (isActive)
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

Mesh* GameObject::GetMesh()
{
	return mesh;
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


GameObject* GameObject::GetChild(int idx)
{
	return Child.at(idx);
}

bool GameObject::inRange(GameObject* targetObj, float Range)
{
	if (abs((targetObj->Translation - Translation).Length()) < Range)
	{
		return true;
	}
	else
	{
		return false;
	}
}

