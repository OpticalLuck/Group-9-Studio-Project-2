#pragma once

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}
	Component& operator=(const Component& rhs)
	{
		Set(rhs.r, rhs.g, rhs.b);
		return *this;
	}
};

struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	unsigned size;
	//to do: add a constructor
	Material(Component kAmbient = Component(0.1f, 0.1f, 0.1f), Component kDiffuse = Component(0.6f, 0.6f, 0.6f), Component kSpecular = Component(0.3f, 0.3f, 0.3f), float kShininess = 5.f, unsigned size = 0) 
	{
		this->kAmbient = kAmbient;
		this->kDiffuse = kDiffuse;
		this->kSpecular = kSpecular;
		this->kShininess = kShininess;
		this->size = size;
	}


	Material& operator=(const Material& rhs)
	{
		kAmbient = rhs.kAmbient;
		kDiffuse = rhs.kDiffuse;
		kSpecular = rhs.kSpecular;
		kShininess = rhs.kShininess;
		size = rhs.size;
	}

};