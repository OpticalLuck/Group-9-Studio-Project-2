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
    void SetTexture(int idx, std::string TextureID);

    // Vector3 halfsize parameter
    // It's basically the radius
    void SetColliderBox(Vector3 halfsize = Vector3(0.5f, 0.5f, 0.5f), Vector3 offsetpos = Vector3(0, 0, 0));

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
    //returns whether this object is within a certain range of another
    bool GetInRange(GameObject* obj, float distance);
    //returns colliderbox
    Collision* GetColliderBox(int idx);
    Vector3 GetCollOffset();
    int GetCollVecSize();
    //returns the render activeness of the gameobj
    bool getActive();

    //to talk about states
    enum FLAGS {
        FLAG0,      //usually idle state
        FLAG1,      //usually basic interaction state
        FLAG2,      //usually big and difficult and specific interaction state
        FLAG3,      //extra specifc state
        TOTALFLAGS  //total number of flags
    };

    //Get the current objects flag
    int getCurrentFlag();
    //Sets current flag
    void SetCurrentFlag(int flag_enum);

    //Gets interactable Radius
    float GetRadius();
    void SetRadius(float rad);

    virtual void Update(double dt);

private:
    //Basic Object Values
    unsigned int ID;
    Mesh* mesh;

    GameObject* Parent;
    std::vector<GameObject*> Child;

    //Transformation
    Vector3 Translation, Rotation, Scale;
    bool IsActive;
    float interactRadius;
       
    std::vector<Collision*> ColliderBox;
    Vector3 CollOffset;
    //which flag it is on
    int flag;

    
};