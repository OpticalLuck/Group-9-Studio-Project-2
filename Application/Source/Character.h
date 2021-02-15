#pragma once
#include "GameObject.h"
class Character : public GameObject
{
public:
	Character(unsigned int ID, Mesh* mesh);
	~Character();
private:
};

