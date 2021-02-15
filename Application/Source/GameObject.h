#pragma once
#include <vector>
#include <string>
#include "Vector3.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Renderer.h"

class GameObject
{
public:
    //constructor(s)
    GameObject();
    //For simple Meshes
    GameObject(Vector3 Position, Mesh* mesh);
    ~GameObject();

    //Mutators
    void SetMesh(Mesh* mesh);
    void SetTexture(std::string TextureID);
    void SetPos(Vector3 Pos);
    void SetTranslate(Vector3 Translate);
    void SetRotate(Vector3 Rotate);
    void SetScale(Vector3 Scale);
    void SetPRotate(Vector3 PivotRotate);
    void SetInteracted(bool state);
    void SetActive(bool Active);
    void bTracking(bool tracking);
    void SetTarget(GameObject* target);
    virtual void Draw(Renderer* renderer, bool EnableLight);
    void AddChild(GameObject* GO);
    void SetIsDead(bool IsDead);

    //Getters
    Mesh* GetMesh();
    Vector3 GetPos();
    Vector3 GetTranslate();
    Vector3 GetRotate();
    Vector3 GetScale();
    Vector3 GetPRotate();
    GameObject* GetChild(int idx);

    bool inRange(GameObject* targetObj, float Range);
    bool getInteracted();
    bool getActive();
    bool getIsDead();
private:
    Mesh* mesh;
    Vector3 Pos;
    GameObject* Parent;
    std::vector<GameObject*> Child;

    //Transformation
    Vector3 Translation, Rotation, Scale, PivotRotate;
    bool Interacted, Active, tracking, IsDead;
};

