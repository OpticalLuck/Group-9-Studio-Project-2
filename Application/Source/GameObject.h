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

    //renders the object
    virtual void Draw(Renderer* renderer, bool EnableLight);

    //Mutators
    void SetID(unsigned int ID);
    void SetMesh(Mesh* mesh);
    void SetTexture(std::string TextureID);

    //Transformation - Orders does not matter as it is handled in renderer
    void SetTranslate(Vector3 Translate);
    void SetRotate(Vector3 Rotate);
    void SetScale(Vector3 Scale);
    
    //sets if object should be rendered true/false
    void SetActive(bool IsActive);

    //adds child for model hierchy purposes
    void AddChild(GameObject* GO);

    //Gets the ID
    const unsigned int GetID();
    //Obtains the mesh
    Mesh* GetMesh();
    //Gets this translatation vector
    Vector3 GetTranslate();
    //Gets this rotation vector
    Vector3 GetRotate();
    //Gets this scaling vector
    Vector3 GetScale();
    //gets the child from the vector array at a certain id (like an array)
    GameObject* GetChild(int idx);

    //returns the activeness of the gameobj
    bool getActive();

private:
    //Basic Object Values
    unsigned int ID;
    Mesh* mesh;

    GameObject* Parent;
    std::vector<GameObject*> Child;

    //Transformation
    Vector3 Translation, Rotation, Scale;
    bool IsActive;
};