#include "Light.h"
#include "GL/glew.h"
#include "Utility.h"
#include <sstream>
#include <string>
#include <iostream>


Light::Light(unsigned m_programID, int count):
	index(count)
{
	std::stringstream ss;
	ss << "lights[" << count << "].position_cameraspace";
	parameters[U_LIGHT_POSITION] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].color";
	parameters[U_LIGHT_COLOR] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].power";
	parameters[U_LIGHT_POWER] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].kC";
	parameters[U_LIGHT_KC] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].kL";
	parameters[U_LIGHT_KL] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].kQ";
	parameters[U_LIGHT_KQ] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].type";
	parameters[U_LIGHT_TYPE] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].spotDirection";
	parameters[U_LIGHT_SPOTDIRECTION] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].cosCutoff";
	parameters[U_LIGHT_COSCUTOFF] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].cosInner";
	parameters[U_LIGHT_COSINNER] = glGetUniformLocation(m_programID, ss.str().c_str());
	ss.str("");
	ss << "lights[" << count << "].exponent";
	parameters[U_LIGHT_EXPONENT] = glGetUniformLocation(m_programID, ss.str().c_str());
}


void Light::Set(LIGHT_TYPE type, Vector3 pos, Color color, float power, float kC, float kL, float kQ, Vector3 spotDirection)
{
	this->type = type;
	position = pos;
	this->color = color;
	this->power = power;
	this->kC = kC;
	this->kL = kL;
	this->kQ = kQ;
	this->spotDirection = spotDirection;
	this->spotDirection = spotDirection;

	cosCutoff = cos(Math::DegreeToRadian(45));
	cosInner = cos(Math::DegreeToRadian(30));
	exponent = 3.f;

	glUniform1i(parameters[U_LIGHT_TYPE], this->type);
	glUniform3fv(parameters[U_LIGHT_COLOR], 1, &this->color.r);
	glUniform1f(parameters[U_LIGHT_POWER], this->power);
	glUniform1f(parameters[U_LIGHT_KC], this->kC);
	glUniform1f(parameters[U_LIGHT_KL], this->kL);
	glUniform1f(parameters[U_LIGHT_KQ], this->kQ);
	glUniform1f(parameters[U_LIGHT_COSCUTOFF], this->cosCutoff);
	glUniform1f(parameters[U_LIGHT_COSINNER], this->cosInner);
	glUniform1f(parameters[U_LIGHT_EXPONENT], this->exponent);
}

void Light::Mode(int LIGHT_TYPE)
{
	switch (LIGHT_TYPE)
	{
	case 0:
		type = LIGHT_POINT;
		break;
	case 1:
		type = LIGHT_DIRECTIONAL;
		break;
	case 2:
		type = LIGHT_SPOT;
		break;
	}
	glUniform1i(parameters[U_LIGHT_TYPE], type);
}

