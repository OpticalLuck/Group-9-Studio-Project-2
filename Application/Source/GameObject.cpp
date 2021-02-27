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
		renderer->PushTransform();
		renderer->GetMStack()->LoadIdentity();
		for (int i = 0; i < ColliderBox.size(); i++)
		{
			Collision* collbox = ColliderBox.at(i);
			renderer->PushTransform();
			renderer->AddTransformation(collbox->GetPos(), collbox->GetRotation(), Vector3(1, 1, 1));
			renderer->RenderMesh(ColliderBox.at(i)->GetCollMesh(), false);
			renderer->PopTransform();
		}
		renderer->PopTransform();
		//if (Child.size() > 0)
		//{
		//	for (int Childidx = 0; Childidx < Child.size(); Childidx++)
		//	{
		//		for (int colinChild = 0; colinChild < Child.at(Childidx)->GetCollVecSize(); colinChild++)
		//		{
		//			Collision Temp = *Child.at(Childidx)->GetColliderBox(colinChild);
		//			renderer->PushTransform();
		//			renderer->AddTransformation(Temp.GetPos(), Temp.GetRotation(), Vector3(1, 1, 1));
		//			renderer->RenderMesh(Temp.GetCollMesh(), false);
		//			renderer->PopTransform();
		//		}
		//	}
		//}
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

void GameObject::LinkColliderToParent()
{
	GameObject* Root = GetRoot();
	GameObject* Current = Parent;
	bool linked = false;
	for (int colidx = 0; colidx < ColliderBox.size(); colidx++)
	{
		while (!linked)
		{
			ColliderBox.at(colidx)->setTranslate(ColliderBox.at(colidx)->GetTranslate() + Current->GetTranslate() + this->GetTranslate());
			ColliderBox.at(colidx)->setRotation(ColliderBox.at(colidx)->GetRotation() + Current->GetRotate());

			if (Root == Current)
			{
				linked = true;
			}
			else
			{
				Current = Current->Parent;
			}
		}
	}
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
	for (int i = 0; i < GO->ColliderBox.size(); i++)
	{
		//GO->LinkColliderToParent();
	}
	Child.push_back(GO);
}

void GameObject::UpdateChildCollision()
{
	if (Child.size() > 0)
	{
		for (int i = 0; i < Child.size(); i++)
		{
			for (int colidx = 0; colidx < Child.at(i)->GetCollVecSize(); colidx++)
			{
				GameObject* root = GetRoot();
				GameObject* current = Child.at(i);
				Vector3 parentpositioninworld(0,0,0);
				Vector3 parentTotalRotation;
				//Calculate position in world space
				while (current != root)
				{
					current = current->Parent;

					parentTotalRotation += current->GetRotate();
					Mtx44 Temp;
					Temp.SetToRotation(current->GetRotate().x, 1, 0, 0);
					parentpositioninworld = Temp * parentpositioninworld;
					Temp.SetToRotation(current->GetRotate().y, 0, 1, 0);
					parentpositioninworld = Temp * parentpositioninworld;
					Temp.SetToRotation(current->GetRotate().z, 0, 0, 1);
					parentpositioninworld = Temp * parentpositioninworld;

					parentpositioninworld += current->GetTranslate();
				}

				current = Child.at(i);
				Collision* temp = Child.at(i)->GetColliderBox(colidx);
				while (current != root)
				{
					Vector3 ParentToChild;
					Mtx44 Rotate;

					//Get Parent Rotation
					Vector3 TotalTranslate = current->GetTranslate();
					Rotate.SetToRotation(parentTotalRotation.x, 1, 0, 0);
					TotalTranslate = Rotate * TotalTranslate;
					Rotate.SetToRotation(parentTotalRotation.y, 0, 1, 0);
					TotalTranslate = Rotate * TotalTranslate;
					Rotate.SetToRotation(parentTotalRotation.z, 0, 0, 1);
					TotalTranslate = Rotate * TotalTranslate;

					ParentToChild = parentpositioninworld + TotalTranslate;
					temp->setTranslate(ParentToChild);
					temp->setRotation(parentTotalRotation);
					//temp->setRotation(parentTotalRotation + Child.at(i)->GetRotate());

					current = current->Parent;
				}
			}

			if (Child.at(i)->Child.size() > 0)
			{
				Child.at(i)->UpdateChildCollision();
			}
		}
	}

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
	for (int i = 0; i < static_cast<int>(Child.size()); i++) {
		Child[i]->SetActive(IsActive);
	}
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

int GameObject::GetNoOfChild()
{
	return Child.size();
}

GameObject* GameObject::GetRoot()
{
	if (Parent)
	{
		return Parent->GetRoot();
	}
	else
	{
		return this;
	}
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
