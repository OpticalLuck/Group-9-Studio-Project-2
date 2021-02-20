#pragma once
#include <map>
#include <string>
class TextureList
{
public:
	TextureList();
	~TextureList();

	unsigned Insert(std::string filename);

private:
	std::map<std::string, unsigned> textureMap;
};

