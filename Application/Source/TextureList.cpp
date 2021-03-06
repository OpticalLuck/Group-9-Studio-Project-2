#include "TextureList.h"
#include "LoadTGA.h"
#include <iostream>

TextureList::TextureList()
{
	std::cout << "Texture Loaded" << std::endl;
}

TextureList::~TextureList()
{
	textureMap.clear();
}

unsigned TextureList::Insert(std::string filename)
{
	std::string directory = "Image//" + filename;
	bool added = false;
	if (textureMap.size() == 0)
	{
		unsigned texture = LoadTGA(directory.c_str());
		textureMap.insert({ filename, texture });
		return texture;
	}
	else
	{
		if (textureMap.find(filename) == textureMap.end())
		{
			unsigned texture = LoadTGA(directory.c_str());
			textureMap.insert({ filename, texture });
			return texture;
		}
		else
		{
			return textureMap.at(filename);
		}
	}
}

