#include "Collision.h"
#include <sstream>
#include "MeshBuilder.h"

Collision::Collision():
    position(NULL),
    halfsize(NULL),
    BoxFrame(nullptr),
    Front(Vector3(0,0,1)),
    Up(Vector3(0,1,0)),
    Right(Vector3(0,0,1))
{
}

Collision::Collision(Vector3 position, Vector3 halfsize):
	position(position),
    halfsize(halfsize),
    DefFront(Vector3(0, 0, 1)),
    DefUp(Vector3(0, 1, 0)),
    DefRight(Vector3(1, 0, 0)),
    Front(Vector3(0, 0, 1)),
    Up(Vector3(0, 1, 0)),
    Right(Vector3(1, 0, 0))
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
    renderer->AddRotate(pitch, yaw, roll);
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
    this->pitch = x;
    this->yaw = y;
    this->roll = z;

    Mtx44 Rotation;

   Rotation.SetToRotation(yaw, 0, 1, 0);
   Front = (Rotation * DefFront).Normalized();
   Right = Front.Cross(DefUp);
   Right.Normalize();

   Rotation.SetToRotation(pitch, 1, 0, 0);
   Front = (Rotation * Front).Normalized();
   Up = Right.Cross(Front);
   Up.Normalize();

   Rotation.SetToRotation(roll, 0, 0, 1);
   Right = (Rotation * Right).Normalized();
   Up = Right.Cross(Front);
   Up.Normalize();

}

Vector3 Collision::GetPos()
{
    return position;
}

Vector3 Collision::Gethalfsize()
{
    return halfsize;
}

float Collision::GetYaw()
{
    return yaw;
}

float Collision::GetPitch()
{
    return pitch;
}

float Collision::GetRoll()
{
    return roll;
}

Vector3 Collision::GetFront()
{
    return Front;
}

Vector3 Collision::GetRight()
{
    return Right;
}

Vector3 Collision::GetUp()
{
    return Up;
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
    //Box 1 - 3 axis
    Vector3 Axis = box1->GetFront();
    return false;
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

