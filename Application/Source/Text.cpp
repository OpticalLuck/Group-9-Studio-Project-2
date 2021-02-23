#include "Text.h"
#include "LoadCSV.h"
#include "MeshBuilder.h"

Text::Text() :
	countdown(false),
	timer(0),
	index(0),
	color(Color(0, 1, 0)),
	mode(STATIC_WORLDTEXT)
{
	SetMesh(MeshBuilder::GenerateText("Text", 16, 16, TextData::GetInstance()->TextDataArr));
	SetTexture(0, "Image//Calibri.tga");
}

Text::~Text()
{
}

void Text::Draw(Renderer* renderer, bool EnableLight)
{
	renderer->PushTransform();
	//scale, translate, rotate
	if (getActive())
	{
		if (mode == STATIC_WORLDTEXT)
		{
			renderer->AddTransformation(GetTranslate(), GetRotate(), GetScale());
			renderer->RenderText(GetMesh(), text, color);
		}
		else if (mode == DIALOGUE_WORLDTEXT)
		{
			renderer->AddTransformation(GetTranslate(), GetRotate(), GetScale());
			renderer->RenderDialogue(GetMesh(), text, color, index);
		}
		else if (mode == STATIC_SCREENTEXT)
		{
			renderer->RenderTextOnScreen(GetMesh(), text, color, 4.f, GetTranslate().x, GetTranslate().y);
		}
	}

	renderer->PopTransform();
}

void Text::SetMode(MODE mode)
{
	this->mode = mode;
}

void Text::SetText(std::string text)
{
	this->text = text;
}

void Text::SetTimer(float timer)
{
	this->timer = timer;
}

void Text::SetColor(Color color)
{
	this->color = color;
}

void Text::StartTimer()
{
	countdown = true;
}

void Text::UpdateTimer(double dt)
{
	//Text Dialogue Timer
	if (countdown)
	{
		if (timer < 0.1f)
		{
			timer += dt;
		}
		else
		{
			timer = 0;
			index++;
		}
	}
}

void Text::RestartTimer()
{
	timer = 0;
	index = 0;
}

void Text::Setindex(int index)
{
	this->index = index;
}

float Text::getTimer()
{
	return timer;
}

int Text::getindex()
{
	return index;
}

std::string Text::GetText()
{
	return text;
}
