#include "GOManager.h"
#include <cassert>

GOManager::GOManager():
	mObjectCount(0)
{
	for (unsigned int i = 0; i < MAX_OBJECT; i++)
	{
		//Prepares the queue of IDs for the GameObjects - FIFO
		mAvailableOBJs.push(i);
	}
}

GOManager::~GOManager()
{
}

GameObject* GOManager::getObj(unsigned int ID)
{
	return OBJECT_MAP.find(ID)->second;
}

