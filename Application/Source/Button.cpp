#include "Button.h"
#include "MeshBuilder.h"
Button::Button(float x, float y, float Width, float Height, float Scale)
{
	xCoord = xdef = x;
	yCoord = ydef = y;
	this->Width = Width;
	this->Height = Height;
	this->Scale = this->DefaultScale = Scale;

	ButtonMesh = MeshBuilder::GenerateQuad("Button", Color(1, 1, 1), Width, Height);
}

Button::~Button()
{
	delete ButtonMesh;
}

void Button::Draw(Renderer* renderer)
{
	renderer->PushTransform();
	renderer->RenderMeshOnScreen(ButtonMesh, xCoord, yCoord, Scale, Scale);
	renderer->PopTransform();
}

void Button::SetTexture(std::string filepath)
{
	ButtonMesh->textureArr[0] = TextureList::GetInstance()->Insert(filepath);
}

void Button::SetbClicked(bool bClicked)
{
	this->bClicked = bClicked;
}

bool Button::isHoveredOn(double xpos, double ypos)
{
	float Button_Left = 10 * (xCoord - (Width * Scale) / 2);
	float Button_Right = 10 * (xCoord + (Width * Scale) / 2);
	float Button_Top = 720 - 10 * (yCoord + (Height * Scale) / 2);
	float Button_Bot = 720 - 10 * (yCoord - (Height * Scale) / 2);

	if (xpos > Button_Left && xpos < Button_Right &&
		ypos < Button_Bot && ypos > Button_Top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::SetxCoord(float x)
{
	xCoord = x;
}

void Button::SetyCoord(float y)
{
	yCoord = y;
}

bool Button::ScaleOnHover(double xpos, double ypos, float UpdatedScale)
{
	if (isHoveredOn(xpos, ypos))
	{
		Scale = DefaultScale * UpdatedScale;
		return true;
	}
	else
	{
		Scale = DefaultScale;
		return false;
	}
}

bool Button::SlideOnHover(double xpos, double ypos, float Distance)
{
	if(isHoveredOn(xpos, ypos))
	{
		xCoord = (1 - 0.5f) * xCoord + 0.5f * (xdef + Distance);
		//rotationval = (1 - ROTATIONSPEED) * target->GetRotate().y + ROTATIONSPEED * CharAngle;
		return true;
	}
	else
	{
		xCoord = (1 - 0.5f) * xCoord + 0.5f * (xdef);
	return false;
	}
}

bool Button::getbClicked() const
{
	return bClicked;
}

float Button::getWidth() const
{
	return Width * Scale;
}

float Button::getHeight() const
{
	return Height * Scale;
}

float Button::getScale() const
{
	return Scale;
}

float Button::getX() const
{
	return xCoord;
}

float Button::getY() const
{
	return yCoord;
}
