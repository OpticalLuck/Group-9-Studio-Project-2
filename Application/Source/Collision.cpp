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
    Front(Vector3(1, 0, 0)),
    Up(Vector3(0, 1, 0)),
    Right(Vector3(0, 0, 1))
{
    Vector3 size = halfsize * 2;
    BoxFrame = MeshBuilder::GenerateWireCube("CollisionBox", Color(0, 1, 0), size.x, size.y, size.z);

    Vertices[0] = position + Front * halfsize.x + Right * halfsize.z + Up * halfsize.y;
    Vertices[1] = position + Front * -halfsize.x + Right * -halfsize.z + Up * -halfsize.y;
    Vertices[2] = position + Front * -halfsize.x + Right * -halfsize.z + Up * halfsize.y;
    Vertices[3] = position + Front * -halfsize.x + Right * halfsize.z + Up * -halfsize.y;
    Vertices[4] = position + Front * halfsize.x + Right * -halfsize.z + Up * -halfsize.y;
    Vertices[5] = position + Front * -halfsize.x + Right * halfsize.z + Up * halfsize.y;
    Vertices[6] = position + Front * halfsize.x + Right * -halfsize.z + Up * halfsize.y;
    Vertices[7] = position + Front * halfsize.x + Right * halfsize.z + Up * -halfsize.y;
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

    RotationMtx.SetToRotation(Rotation.z, 0, 0, 1);
    Front = RotationMtx * Vector3(1, 0, 0);
    Up = RotationMtx * Vector3(0, 1, 0);
    Right = RotationMtx * Vector3(0, 0, 1);

    RotationMtx.SetToRotation(Rotation.y, 0, 1, 0);
    Front = RotationMtx * Front;
    Up = RotationMtx * Up;
    Right = RotationMtx * Right;

    RotationMtx.SetToRotation(Rotation.x, 1, 0, 0);
    Front = RotationMtx * Front;
    Right = RotationMtx * Right;
    Up = RotationMtx * Up;

    Vertices[0] = position + Front * halfsize.x + Right * halfsize.z + Up * halfsize.y;
    Vertices[1] = position + Front * -halfsize.x + Right * -halfsize.z + Up * -halfsize.y;
    Vertices[2] = position + Front * -halfsize.x + Right * -halfsize.z + Up * halfsize.y;
    Vertices[3] = position + Front * -halfsize.x + Right * halfsize.z + Up * -halfsize.y;
    Vertices[4] = position + Front * halfsize.x + Right * -halfsize.z + Up * -halfsize.y;
    Vertices[5] = position + Front * -halfsize.x + Right * halfsize.z + Up * halfsize.y;
    Vertices[6] = position + Front * halfsize.x + Right * -halfsize.z + Up * halfsize.y;
    Vertices[7] = position + Front * halfsize.x + Right * halfsize.z + Up * -halfsize.y;

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

bool Collision::CheckOBBCollision(Collision* box1, Collision* box2)
{
    bool Front_1 = false;
    bool Right_1 = false;
    bool Up_1 = false;
    bool Front_2 = false;
    bool Right_2 = false;
    bool Up_2 = false;
    bool Cross_1 = false;
    bool Cross_2 = false;
    bool Cross_3 = false;
    bool Cross_4 = false;
    bool Cross_5 = false;
    bool Cross_6 = false;
    bool Cross_7 = false;
    bool Cross_8 = false;
    bool Cross_9 = false;

    //Box 1 - 3 axis
    Vector3 Axis = box1->GetFront();
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
       ( box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
        box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)))
    {
        Front_1 = true;
    }

    Axis = box1->GetUp();
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
       ( box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
        box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)))
    {
        Up_1 = true;;
    }

    Axis = box1->GetRight();
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)))
    {
        Right_1 = true;;
    }
    
    //Box 2 - 3 axis
    Axis = box2->GetFront();
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)))
    {
        Front_2 = true;
    }

    Axis = box2->GetRight();
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)))
    {
        Right_2 = true;
    }

    Axis = box2->GetUp();
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)))
    {
        Up_2 = true;
    }

    Axis = box1->GetFront().Cross(box2->GetFront());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0,0,0))
    {
        Cross_1 = true;
    }

    Axis = box1->GetFront().Cross(box2->GetRight());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_2 = true;
    }

    Axis = box1->GetFront().Cross(box2->GetUp());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_3 = true;
    }

    Axis = box1->GetRight().Cross(box2->GetFront());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_4 = true;
    }

    Axis =box1->GetRight().Cross(box2->GetUp());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_5 = true;
    }

    Axis = box1->GetRight().Cross(box2->GetRight());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_6 = true;
    }

    Axis = box1->GetUp().Cross(box2->GetFront());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_7 = true;
    }

    Axis = box1->GetUp().Cross(box2->GetUp());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_8 = true;
    }

    Axis = box1->GetUp().Cross(box2->GetRight());
    if ((box1->GetLowestVal(Axis) < box2->GetHighestVal(Axis) &&
        box1->GetLowestVal(Axis) > box2->GetLowestVal(Axis)) ||
        (box2->GetLowestVal(Axis) < box1->GetHighestVal(Axis) &&
            box2->GetHighestVal(Axis) > box1->GetLowestVal(Axis)) ||
        Axis == Vector3(0, 0, 0))
    {
        Cross_9 = true;
    }

    return Front_1 && Up_1 && Right_1 && Front_2 && Right_2 && Up_2 && Cross_1 && Cross_2 && Cross_3 && Cross_4 && Cross_5 && Cross_6 && Cross_7 && Cross_8 && Cross_9;
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
    Vector3 Diff_1 = box2->GetHighestVal(axis) - box1->GetLowestVal(axis);
    Vector3 Diff_2 = box1->GetHighestVal(axis) - box2->GetLowestVal(axis);

    //Returs negative and positive on one side - For directions
    if (Diff_1.Length() > Diff_2.Length())
    {
        return Diff_2 * -1;
    }
    else
    {
        return Diff_1;
    }
}

float Collision::GetLowestVal(Vector3 axis)
{
    float Lowest = axis.Dot(Vertices[0]);
    for (int i = 1; i < 8; i++)
    {
        if (Lowest > axis.Dot(Vertices[i]))
        {
            Lowest = axis.Dot(Vertices[i]);
        }
    }
    return Lowest;
}

float Collision::GetHighestVal(Vector3 axis)
{
    float Highest = axis.Dot(Vertices[0]);
    for (int i = 1; i < 8; i++)
    {
        if (Highest < axis.Dot(Vertices[i]))
        {
            Highest = axis.Dot(Vertices[i]);
        }
    }
    return Highest;
}

