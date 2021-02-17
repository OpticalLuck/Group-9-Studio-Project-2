#include "Collision.h"
#include <sstream>
#include "MeshBuilder.h"

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

void Collision::DrawFrame(Renderer* renderer)
{
    renderer->PushTransform();
    renderer->AddTranslate(position.x, position.y, position.z);
    renderer->AddRotate(Rotation.x, Rotation.y, Rotation.z);
    renderer->RenderMesh(BoxFrame, false);
    renderer->PopTransform();
}

void Collision::setcollpos(Vector3 position)
{
    this->position = position;
}

void Collision::sethalfsize(Vector3 halfsize)
{
    this->halfsize = halfsize;
}

void Collision::setRotation(float x, float y, float z)
{
    Rotation = Vector3(x, y, z);

    Mtx44 RotationMtx;

    RotationMtx.SetToRotation(Rotation.x, 1, 0, 0);
    Front = RotationMtx * Vector3(1, 0, 0);
    Up = RotationMtx * Vector3(0, 1, 0);
    Right = RotationMtx * Vector3(0, 0, 1);

    RotationMtx.SetToRotation(Rotation.y, 0, 1, 0);
    Front = RotationMtx * Front;
    Up = RotationMtx * Up;
    Right = RotationMtx * Right;

    RotationMtx.SetToRotation(Rotation.z, 0, 0, 1);
    Front = RotationMtx * Front;
    Right = RotationMtx * Right;
    Up = RotationMtx * Up;
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

bool Collision::CheckAABBCollision(Collision* box1, Collision* box2)
{
    // collision x-axis
    bool collisionX = abs(box1->position.x - box2->position.x) < (box1->halfsize.x + box2->halfsize.x);

    // collision y-axis
    bool collisionY = abs(box1->position.y - box2->position.y) < (box1->halfsize.y + box2->halfsize.y);

    // collision z-axis
    bool collisionZ = abs(box1->position.z - box2->position.z) < (box1->halfsize.z + box2->halfsize.z);

    // collision only if on both axes
    return collisionX && collisionY && collisionZ;
}

Info Collision::CheckOBBCollision(Collision* box1, Collision* box2)
{
    Vector3 Axis = box1->Front;
    bool isCollided = true;
    float diff = getSeparatingPlane(box1->position - box2->position, Axis, box1, box2);
    if (diff < 0)
    {
        isCollided = false;
    }

    float diff2;
    auto lambda = [&](Vector3 axis)
    {
        diff2 = getSeparatingPlane(box1->position - box2->position, axis, box1, box2 );
        if (diff > diff2)
        {
            Axis = axis;
            diff = diff2;
        }
        if (diff < 0)
        {
            isCollided = false;
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

    return Info(Axis, isCollided);
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

float Collision::getXmin()
{
    return position.x - halfsize.x;
}

float Collision::getXmax()
{
    return position.x + halfsize.x;
}

float Collision::getYmin()
{
    return position.y - halfsize.y;
}

float Collision::getYmax()
{
    return position.y + halfsize.y;
}

float Collision::getZmin()
{
    return position.z - halfsize.z;
}

float Collision::getZmax()
{
    return position.z + halfsize.z;
}

float Collision::getDiffX(Collision* box1, Collision* box2)
{
    float XDiff_1 = box2->getXmax() - box1->getXmin();
    float XDiff_2 = box1->getXmax() - box2->getXmin();

    //Returs negative and positive on one side - For directions
    if (XDiff_1 > XDiff_2)
    {
        return XDiff_2 * - 1;
    }
    else
    {
        return XDiff_1;
    }
}

float Collision::getDiffY(Collision* box1, Collision* box2)
{
    float YDiff_1 = box2->getYmax() - box1->getYmin();
    float YDiff_2 = box1->getYmax() - box2->getYmin();

    //Returs negative and positive on one side - For directions
    if (YDiff_1 > YDiff_2)
    {
        return YDiff_2 * -1;
    }
    else
    {
        return YDiff_1;
    }
}

float Collision::getDiffZ(Collision* box1, Collision* box2)
{
    float ZDiff_1 = box2->getZmax() - box1->getZmin();
    float ZDiff_2 = box1->getZmax() - box2->getZmin();

    //Returs negative and positive on one side - For directions
    if (ZDiff_1 > ZDiff_2)
    {
        return ZDiff_2 * -1;
    }
    else
    {
        return ZDiff_1;
    }
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

float Collision::ProjectTo(Vector3 axis, Vector3 box1val, Vector3 box2val)
{
    return (box1val - box2val).Dot(axis) / axis.Length();
}

