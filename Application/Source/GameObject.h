#pragma once
#include <vector>
#include <string>
#include "Vector3.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Renderer.h"
#include "Collision.h"

class GameObject
{
public:
    //constructor(s)
    GameObject();
    GameObject(unsigned int ID, Mesh* mesh);
    ~GameObject();

    virtual void Draw(Renderer* renderer, bool EnableLight);
    
    //Mutators
    void SetID(unsigned int ID);
    void SetMesh(Mesh* mesh);
    void SetTexture(std::string TextureID);
    
    //Transformation - Orders does not matter as it is handled in renderer
    void SetTranslate(Vector3 Translate);
    void SetRotate(Vector3 Rotate);
    void SetScale(Vector3 Scale);
    
    void SetActive(bool IsActive);

    void AddChild(GameObject* GO);

    //Getters
    const unsigned int GetID();
    Mesh* GetMesh();
    Vector3 GetTranslate();
    Vector3 GetRotate();
    Vector3 GetScale();
    GameObject* GetChild(int idx);

    bool getActive();

private:
    //Basic Object Values
    unsigned int ID;
    Mesh* mesh;

    //Collision
    Collision* CollisionBox;

    GameObject* Parent;
    std::vector<GameObject*> Child;

    //Transformation
    Vector3 Translation, Rotation, Scale;
    bool IsActive;
};