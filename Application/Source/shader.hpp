#pragma once
#include "Singleton.h"

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

class Shader : public Singleton<Shader>
{
public:
	unsigned shaderdata;
	Shader() { shaderdata = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader"); };
private:
};
