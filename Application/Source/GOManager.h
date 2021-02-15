#pragma once
#include "GameObject.h"
#include "Character.h"

#include <cassert>
#include <queue>
#include <map>
//Handles Creating and Destroying GOs
class GOManager
{
public:
	GOManager();
	~GOManager();
	
	template <class C>
	C* CreateGO(Mesh* mesh);

	template <class C>
	void DestroyGO(C* Object);

	GameObject* getObj(unsigned int ID);

private:
	const unsigned int MAX_OBJECT = 100;
	std::queue<unsigned int> mAvailableOBJs;
	unsigned int mObjectCount;
	std::map<unsigned int, GameObject*> OBJECT_MAP;
};

template<class C>
inline C* GOManager::CreateGO(Mesh* mesh)
{
	assert(mObjectCount < MAX_OBJECT && "Too many Objects.");

	//Get ID at the front of the queue
	unsigned int id = mAvailableOBJs.front();
	//Pop ID from the Queue
	mAvailableOBJs.pop();
	//Increase OBJ Count
	++mObjectCount;

	C* GO = new C(id, mesh);

	//Insert GO into map
	OBJECT_MAP.insert({ id, GO });

	return GO;
}

template<class C>
inline void GOManager::DestroyGO(C* Object)
{
	assert(Object->GetID() < MAX_OBJECT && "Object ID out of range");

	mAvailableOBJs.push(Object->GetID());
	--mObjectCount;

	delete Object;
}
