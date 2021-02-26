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
	bool isHoveredOn(double xpos, double ypos);
	void SetxCoord(float x);
	void SetyCoord(float y);

	bool getbClicked() const;
	float getWidth() const;
	float getHeight() const;
	float getScale() const;
	float getX() const;
	float getY() const;
private:
	Mesh* ButtonMesh;
	float xCoord, yCoord;
	float Width, Height;
	float DefaultScale, Scale;
	bool bClicked;
};

