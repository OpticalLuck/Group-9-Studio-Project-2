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
	interactRadius(3)
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
	interactRadius(3)
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

	if (Collision::isRender)
	{
		for (int i = 0; i < ColliderBox.size(); i++)
		{

			Collision* collbox = ColliderBox.at(i);
			renderer->PushTransform();
			renderer->AddTransformation(collbox->GetPos(), collbox->GetRotation(), Vector3(1, 1, 1));
			renderer->RenderMesh(ColliderBox.at(i)->GetCollMesh(), false);
			renderer->PopTransform();

		}
	}
}



void GameObject::SetID(unsigned int ID)
{
	this->ID = ID;
}

void GameObject::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void GameObject::SetTexture(int idx, std::string TextureID)
{
	mesh->textureArr[0] = LoadTGA(TextureID.c_str());
}

void GameObject::SetColliderBox(Vector3 halfsize, Vector3 offsetpos)
{
	Collision* temp = new Collision(Translation, offsetpos, halfsize);
	temp->setRotation(Rotation);
	ColliderBox.push_back(temp);
}

void GameObject::SetTranslate(Vector3 Translate)
{
	Translation = Translate;

	//Update Hitbox Position
	for (int i = 0; i < GetCollVecSize(); i++)
	{
		GetColliderBox(i)->setTranslate(GetTranslate());
	}
}
void GameObject::SetRotate(Vector3 Rotate)
{
	if (Rotate.x > 360)
	{
		Rotate.x -= 360;
	}
	if (Rotate.x < 0)
	{
		Rotate.x += 360;
	}
	if (Rotate.y > 360)
	{
		Rotate.y -= 360;
	}
	if (Rotate.y < 0)
	{
		Rotate.y += 360;
	}
	if (Rotate.z > 360)
	{
		Rotate.z -= 360;
	}
	if (Rotate.z < 0)
	{
		Rotate.z += 360;
	}
	Rotation = Rotate;
	for (int i = 0; i < ColliderBox.size(); i++)
	{
		ColliderBox.at(i)->setRotation(Rotate);
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

void GameObject::CollisionResolution(GameObject* target)
{
	for (int i = 0; i < GetCollVecSize(); i++)
	{
		for (int j = 0; j < target->GetCollVecSize(); j++)
		{
			Info CollisionInfo = ColliderBox.at(i)->CheckOBBCollision(target->GetColliderBox(j));

			if (CollisionInfo.Collided)
			{
				Collision* objBox = ColliderBox.at(i);
				Collision* targetBox = target->GetColliderBox(j);
				float distance = CollisionInfo.distance;
				if ((objBox->GetPos() - targetBox->GetPos()).Dot(CollisionInfo.Axis) < 0)
				{
					distance = distance * -1;
				}

				Translation += distance * CollisionInfo.Axis;
				for(int updateidx = 0; updateidx < GetCollVecSize(); updateidx++)
					ColliderBox.at(updateidx)->setTranslate(Translation);

				

			}
		}
	}
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
	return (abs((obj->GetTranslate() - this->GetTranslate()).Length()) < distance );
}

Collision* GameObject::GetColliderBox(int idx)
{
	return ColliderBox.at(idx);
}

int GameObject::GetCollVecSize()
{
	return ColliderBox.size();
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
