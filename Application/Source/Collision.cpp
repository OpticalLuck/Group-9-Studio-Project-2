#include "Collision.h"
#include <sstream>
#include "MeshBuilder.h"
#include "GameObject.h"

bool Collision::isRender = false;

Collision::Collision():
    translate(NULL),
    halfsize(NULL),
    BoxFrame(nullptr),
    Front(Vector3(1,0,0)),
    Up(Vector3(0,1,0)),
    Right(Vector3(0,0,1))
{
}

Collision::Collision(Vector3 translate, Vector3 offset, Vector3 halfsize) :
    translate(translate),
    halfsize(halfsize),
    DefaultHalfSize(halfsize),
    offsetpos(offset),
    Front(Vector3(1, 0, 0)),
    Up(Vector3(0, 1, 0)),
    Right(Vector3(0, 0, 1))
{
    Vector3 size = halfsize * 2;
    BoxFrame = MeshBuilder::GenerateWireCube("CollisionBox", Color(0, 1, 0), size.x, size.y, size.z);
}

Collision::~Collision()
{
    if(BoxFrame)
        delete BoxFrame;
}

void Collision::setTranslate(Vector3 translate)
{
    this->translate = translate;
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

Vector3 Collision::GetPos()
{
    return translate + offsetpos;
}

Vector3 Collision::GetTranslate()
{
    return translate;
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

Info Collision::CheckOBBCollision(Collision* target)
{
    Vector3 Axis = Front;
    bool isCollided = true;
    float diff = getSeparatingPlane(GetPos() - target->GetPos(), Axis.Normalized(), target);
    if (diff < 0)
    {
        isCollided = false;
    }

    float diff2;
    auto lambda = [&](Vector3 axis)
    {
        if (axis != Vector3(0, 0, 0))
        {
            diff2 = getSeparatingPlane(GetPos() - target->GetPos(), axis.Normalized(), target );
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


    lambda(Right);
    lambda(Up);
    lambda(target->Front);
    lambda(target->Right);
    lambda(target->Up);
    lambda(Front.Cross(target->Front));
    lambda(Front.Cross(target->Right));
    lambda(Front.Cross(target->Up));
    lambda(Right.Cross(target->Front));
    lambda(Right.Cross(target->Right));
    lambda(Right.Cross(target->Up));
    lambda(Up.Cross(target->Front));
    lambda(Up.Cross(target->Right));
    lambda(Up.Cross(target->Up));

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

float Collision::getSeparatingPlane(const Vector3 RPos, const Vector3 Plane, const Collision* target)
{
    return (fabs((Front * halfsize.x).Dot(Plane)) +
            fabs((Up * halfsize.y).Dot(Plane)) +
            fabs((Right * halfsize.z).Dot(Plane)) +
            fabs((target->Front * target->halfsize.x).Dot(Plane)) +
            fabs((target->Up * target->halfsize.y).Dot(Plane)) +
            fabs((target->Right * target->halfsize.z).Dot(Plane))) - (fabs(RPos.Dot(Plane)));
}