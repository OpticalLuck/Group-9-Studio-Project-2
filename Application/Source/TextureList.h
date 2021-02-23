#pragma once
#include <map>
#include <string>
#include "Singleton.h"

class TextureList : public Singleton<TextureList>
{
public:
	TextureList();
	~TextureList();

	unsigned Insert(std::string filename);

private:
	std::map<std::string, unsigned> textureMap;
};

