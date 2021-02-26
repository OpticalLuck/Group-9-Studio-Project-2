#pragma once
#include "Mesh.h"
#include "Renderer.h"
class Button
{
public:
	Button(float x, float y, float Width, float Height, float Scale);
	~Button();

	void Draw(Renderer* renderer);

	void SetTexture(std::string filepath);
	void SetbClicked(bool bClicked);
	void SetxCoord(float x);
	void SetyCoord(float y);

	bool ScaleOnHover(double xpos, double ypos, float UpdatedScale);
	bool SlideOnHover(double xpos, double ypos, float Distance);
	bool isHoveredOn(double xpos, double ypos);
	bool getbClicked() const;
	float getWidth() const;
	float getHeight() const;
	float getScale() const;
	float getX() const;
	float getY() const;
private:
	Mesh* ButtonMesh;
	float xCoord, yCoord;
	float xdef, ydef;
	float Width, Height;
	float DefaultScale, Scale;
	bool bClicked;
};

