#pragma once
#include <bitset>
#include "Vector3.h"
#include "MyMath.h"
//Simple Alias
using ComponentType = std::uint8_t;

//Used to define arr size later 
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
struct Transform
{
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;
};