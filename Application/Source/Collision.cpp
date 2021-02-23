#include "Collision.h"
#include <sstream>
#include "MeshBuilder.h"
#include "GameObject.h"

bool Collision::isRender = true;

Collision::Collision():
    position(NULL),
    halfsize(NULL),
    BoxFrame(nullptr),
    Front(Vector3(1,0,0)),
    Up(Vector3(0,1,0)),
    Right(Vector3(0,0,1))
{
}

Collision::Collision(Vector3 position, Vector3 halfsize) :
    position(position),
    halfsize(halfsize),
    DefaultHalfSize(halfsize),
    Front(Vector3(1, 0, 0)),
    Up(Vector3(0, 1, 0)),
    Right(Vector3(0, 0, 1))
{
    Vector3 size = halfsize * 2;
    BoxFrame = MeshBuilder::GenerateWireCube("CollisionBox", Color(0, 1, 0), size.x, size.y, size.z);
}

Collision::~Collision()
{
}

void Collision::setTranslate(Vector3 position)
{
    this->position = position;
}

void Collision::sethalfsize(Vector3 halfsize)
{
    this->halfsize = halfsize;
}

void Collision::setRotation(Vector3 rotation)
{
    Rotation = rotation;
    Mtx44 RotationMtx;

    RotationMtx.SetToRotation(rotation.x, 1, 0, 0);
    Front = RotationMtx * Vector3(1, 0, 0);
    Up = RotationMtx * Vector3(0, 1, 0);
    Right = RotationMtx * Vector3(0, 0, 1);

    RotationMtx.SetToRotation(rotation.y, 0, 1, 0);
    Front = RotationMtx * Front;
    Up = RotationMtx * Up;
    Right = RotationMtx * Right;

    RotationMtx.SetToRotation(rotation.z, 0, 0, 1);
    Front = RotationMtx * Front;
    Right = RotationMtx * Right;
    Up = RotationMtx * Up;
}

void Collision::setOffsetpos(Vector3 offset)
{
    this->offsetpos = offset;
}

void Collision::OBBResolution(GameObject* object, GameObject* target)
{
    for (int i = 0; i < object->GetCollVecSize(); i++)
    {
        for (int j = 0; j < target->GetCollVecSize(); j++)
        {
            Info CollisionInfo = Collision::CheckOBBCollision(object->GetColliderBox(i), target->GetColliderBox(j));

            if (CollisionInfo.Collided)
            {
                Collision* objBox = object->GetColliderBox(i);
                Collision* targetBox = target->GetColliderBox(j);
                float distance = CollisionInfo.distance;
                if ((objBox->GetPos() - targetBox->GetPos()).Dot(CollisionInfo.Axis) < 0)
                {
                    distance = distance * -1;
                }

                object->SetTranslate(object->GetTranslate() + distance * CollisionInfo.Axis);
            }
        }
    }
    
}

Vector3 Collision::GetPos()
{
    return position;
}

Vector3 Collision::Gethalfsize()
{
    return halfsize;
}

Vector3 Collision::GetRotation()
{
    return Rotation;
}

Mesh* Collision::GetCollMesh()
{
    return BoxFrame;
}

Info Collision::CheckOBBCollision(Collision* box1, Collision* box2)
{
    Vector3 Axis = box1->Front;
    bool isCollided = true;
    float diff = getSeparatingPlane(box1->position - box2->position, Axis.Normalized(), box1, box2);
    if (diff < 0)
    {
        isCollided = false;
    }


    float diff2;
    auto lambda = [&](Vector3 axis)
    {
        if (axis != Vector3(0, 0, 0))
        {
            diff2 = getSeparatingPlane(box1->position - box2->position, axis.Normalized(), box1, box2 );
            if (diff > diff2)
            {
                Axis = axis.Normalized();
                diff = diff2;
            }
            if (diff < 0)
            {
                isCollided = false;
            }
        }
    };


    lambda(box1->Right);
    lambda(box1->Up);
    lambda(box2->Front);
    lambda(box2->Right);
    lambda(box2->Up);
    lambda(box1->Front.Cross(box2->Front));
    lambda(box1->Front.Cross(box2->Right));
    lambda(box1->Front.Cross(box2->Up));
    lambda(box1->Right.Cross(box2->Front));
    lambda(box1->Right.Cross(box2->Right));
    lambda(box1->Right.Cross(box2->Up));
    lambda(box1->Up.Cross(box2->Front));
    lambda(box1->Up.Cross(box2->Right));
    lambda(box1->Up.Cross(box2->Up));

    return Info(Axis, diff, isCollided);
}

Vector3 Collision::GetFront()
{
    return Front;
}

Vector3 Collision::GetUp()
{
    return Up;
}

Vector3 Collision::GetRight()
{
    return Right;
}

Vector3 Collision::GetOffsetpos()
{
    return offsetpos;
}

Vector3 Collision::getDiff(Vector3 axis, Collision* box1, Collision* box2)
{
    return Vector3();
}

float Collision::getSeparatingPlane(const Vector3 RPos, const Vector3 Plane, const Collision* box1, const Collision* box2)
{
    return (fabs((box1->Front * box1->halfsize.x).Dot(Plane)) +
            fabs((box1->Up * box1->halfsize.y).Dot(Plane)) +
            fabs((box1->Right * box1->halfsize.z).Dot(Plane)) +
            fabs((box2->Front * box2->halfsize.x).Dot(Plane)) +
            fabs((box2->Up * box2->halfsize.y).Dot(Plane)) +
            fabs((box2->Right * box2->halfsize.z).Dot(Plane))) - (fabs(RPos.Dot(Plane)));
}