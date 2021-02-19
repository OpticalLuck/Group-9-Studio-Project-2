#include "GameObject.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

GameObject::GameObject() :
	mesh(nullptr),
	IsActive(true),
	Translation(Vector3(0, 0, 0)),
	Scale(Vector3(1, 1, 1)),
	Rotation(Vector3(0, 0, 0)),
	Parent(nullptr),
	ID(0),
	flag(FLAG0),
	interactRadius(3),
	ColliderBox(nullptr)
{
}

GameObject::GameObject(unsigned int ID, Mesh* mesh) :
	ID(ID),
	mesh(nullptr),
	IsActive(true),
	Translation(Vector3(0, 0, 0)),
	Scale(Vector3(1, 1, 1)),
	Rotation(Vector3(0, 0, 0)),
	Parent(nullptr),
	flag(FLAG0),
	interactRadius(3),
	ColliderBox(nullptr)
{
	this->mesh = mesh;
}

GameObject::~GameObject()
{
}

void GameObject::Draw(Renderer* renderer, bool EnableLight)
{
	renderer->PushTransform();
	//scale, translate, rotate
	renderer->AddTransformation(Translation, Rotation, Scale);
	if (IsActive)
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



void GameObject::SetID(unsigned int ID)
{
	this->ID = ID;
}

void GameObject::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void GameObject::SetTexture(std::string TextureID)
{
	mesh->textureID = LoadTGA(TextureID.c_str());
}

void GameObject::SetColliderBox(Vector3 halfsize)
{
	ColliderBox = new Collision(Translation, halfsize);
}

void GameObject::SetTranslate(Vector3 Translate)
{
	Translation = Translate;
	if (ColliderBox)
	{
		ColliderBox->setTranslate(Translate);
	}
}

void GameObject::SetRotate(Vector3 Rotate)
{
	Rotation = Rotate;
	if (ColliderBox)
	{
		ColliderBox->setRotation(Rotate);
	}
}

void GameObject::SetScale(Vector3 Scale)
{
	this->Scale = Scale;
}

void GameObject::AddChild(GameObject* GO)
{
	GO->Parent = this;
	Child.push_back(GO);
}

void GameObject::SetActive(bool IsActive)
{
	this->IsActive = IsActive;
}

const unsigned int GameObject::GetID()
{
	return ID;
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

bool GameObject::GetInRange(GameObject* obj, float distance)
{
	
	return (abs((this->GetTranslate() - obj->GetTranslate()).Length()) < distance );
}

Collision* GameObject::GetColliderBox()
{
	return ColliderBox;
}

bool GameObject::getActive()
{
	return IsActive;
}

int GameObject::getCurrentFlag()
{
	return flag;
}

void GameObject::SetCurrentFlag(int flag_enum)
{
	flag = flag_enum;
}

float GameObject::GetRadius()
{
	return interactRadius;
}

void GameObject::SetRadius(float rad)
{
	interactRadius = rad;
}

void GameObject::Update(double dt)
{
	//does nothing
}
