#include "SceneText.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"

SceneText::SceneText() :
	fps(0.f)
{
}

SceneText::~SceneText()
{
}

void SceneText::Init()
{
	renderer = new Renderer();

	Axis = new GameObject(Vector3(0, 0, 0), MeshBuilder::GenerateAxes("Axes", 1000, 1000, 1000));
	for (int i = 0; i < 4; i++)
	{
		lights[i] = new Light(renderer->GetprogramID(), i);
	}

	//meshlist
	meshlist = new MeshList();

	//SkyBox
	skybox = new SkyBox();

	//Environment
	environment = new Environment(meshlist);

	//Character
	Characters = new Character(meshlist);

	camera2.Init(Characters->GetCharacter(Characters->CHAR_AMRED)->GetPos(), Vector3(0, 0, -1), Vector3(0, 1, 0));
	camera2.SetTarget(Characters->GetCharacter(Characters->CHAR_AMRED)->GetPos());

	FallGuys = new A1FG();

	//TEXT
	text[0] = new Text();
	text[0]->SetMode(text[0]->STATIC_WORLDTEXT);
	text[0]->SetText("Press F to Eject Pink Guy");
	text[0]->SetPos(Vector3(-3.5f, 4, 0));

	text[1] = new Text();
	text[1]->SetMode(text[1]->STATIC_SCREENTEXT);
	text[1]->SetText("Left Click to kill");

	text[1]->SetColor(Color(1, 0, 0));
	text[1]->SetPos(Vector3(28, 32, 0));
	text[1]->SetActive(false);

	text[2] = new Text();
	text[2]->SetMode(text[2]->STATIC_WORLDTEXT);
	text[2]->SetText("Left Click to kill");
	text[2]->SetColor(Color(1, 0, 0));

	text[2]->SetTranslate(Vector3(-5,8,0));
	text[2]->SetScale(Vector3(5, 5, 5));
	text[2]->SetActive(false);
	Characters->GetCharacter(Characters->CHAR_AMGREEN)->AddChild(text[2]);

	text[3] = new Text();
	text[3]->SetMode(text[3]->DIALOGUE_WORLDTEXT);
	text[3]->SetPos(Vector3(-4, 4, -30));
	text[3]->SetText("PinkGuy was An Imposter.");
	text[3]->SetColor(Color(1, 1, 1));

	text[4] = new Text();
	text[4]->SetMode(text[4]->STATIC_WORLDTEXT);
	text[4]->SetText("Pull Lever to eject garbage");
	text[4]->SetColor(Color(0, 1, 0));
	text[4]->SetPos(Vector3(20.8, 6, -20));
	text[4]->SetRotate(Vector3(0, -45, 0));

	text[5] = new Text();
	{
	lights[0]->Set(Light::LIGHT_POINT,
		           Vector3(10, 9, -10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));

	lights[1]->Set(Light::LIGHT_POINT,
				   Vector3(10, 9, 10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));

	lights[2]->Set(Light::LIGHT_POINT,
				   Vector3(-10, 9, -10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));

	lights[3]->Set(Light::LIGHT_POINT,
				   Vector3(-10, 9, 10),
				   Color(1, 1, 1),
				   1.f, 1.f, 0.01f, 0.001f,
				   Vector3(0.f, 1.f, 0.f));
	}

	//Update the light model pos to match light source
	environment->SetCoord(environment->OBJ_LIGHT1, lights[0]->position);
	environment->SetCoord(environment->OBJ_LIGHT2, lights[1]->position);
	environment->SetCoord(environment->OBJ_LIGHT3, lights[2]->position);
	environment->SetCoord(environment->OBJ_LIGHT4, lights[3]->position);
}	

float timepassed = 0.f;
void SceneText::Update(double dt)
{
	fps = 1.f / dt;
	camera2.Updatemovement(dt);
	if (camera2.GetMode() != camera2.ANIMATION)
	{
		Characters->GetCharacter(Characters->CHAR_AMRED)->SetPos(camera2.GetObjPos() + Vector3(0, -1, 0));
		Characters->GetCharacter(Characters->CHAR_AMRED)->SetRotate(Vector3(0, 90 - camera2.GetYaw(), 0));
	}

	static bool bLButtonState = false;
	//Debug
	{
		if (Application::IsKeyPressed('1'))
		{
			glEnable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('2'))
		{
			glDisable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('3'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (Application::IsKeyPressed('4'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		//Input
		if (Application::IsKeyPressed('9'))
		{
			Application::EnableCursor();
		}
		if (Application::IsKeyPressed('0'))
		{
			Application::DisableCursor();
		}

		if (Application::IsKeyPressed('N'))
		{
			camera2.ToggleMode(camera2.FIRST_PERSON);
			Vector3 Me = Characters->GetCharacter(Characters->CHAR_AMRED)->GetPos();
			camera2.SetPosition(Vector3(Me.x, Me.y + 1, Me.z));
		}
		if (Application::IsKeyPressed('M'))
		{
			camera2.ToggleMode(camera2.THIRD_PERSON);
			Vector3 Me = Characters->GetCharacter(Characters->CHAR_AMRED)->GetPos(); 
			if (camera2.GetMode() != camera2.THIRD_PERSON)
			{
				camera2.SetPosition(Vector3(Me.x, Me.y + 1, Me.z));
			}
		}
		if (Application::IsKeyPressed('B'))
		{
			camera2.ToggleMode(camera2.FREE_VIEW);
		}
	}

	if (Application::IsKeyPressed('F'))
	{
		if (Characters->GetCharacter(Characters->CHAR_AMRED)->inRange(environment->GetArr(environment->OBJ_TABLE1), 4.f))
		{
			environment->GetArr(environment->OBJ_BTN)->SetInteracted(true);
		}
	}
	//Button Click
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;

		//Enable Kill Animation
		if (Characters->GetCharacter(Characters->CHAR_AMRED)->inRange(Characters->GetCharacter(Characters->CHAR_AMGREEN), 5.f) && !Characters->GetCharacter(Characters->CHAR_AMGREEN)->getIsDead())
		{
			//Disable Text
			text[1]->SetActive(false);
			text[2]->SetActive(false);

			//Me to GreenAM
			Vector3 Direction = Characters->GetCharacter(Characters->CHAR_AMGREEN)->GetPos() - Characters->GetCharacter(Characters->CHAR_AMRED)->GetPos();
			float Dist = 4;

			//Setting Camera Position
			camera2.SetPosition(Characters->GetCharacter(Characters->CHAR_AMGREEN)->GetPos() - Dist * Direction.Normalized());
			camera2.SetView(Direction);

			//Updating RedAM
			Characters->GetCharacter(Characters->CHAR_AMRED)->SetPos(camera2.GetPosition());
			Characters->GetCharacter(Characters->CHAR_AMRED)->SetRotate(Vector3(0, 90 - camera2.GetYaw(), 0));
			camera2.SetTarget(Characters->GetCharacter(Characters->CHAR_AMRED)->GetPos());

			camera2.ToggleAnimation(Dist);

			Characters->GetCharacter(Characters->CHAR_AMGREEN)->SetInteracted(true);
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
	else if (Application::IsMousePressed(0))
	{
		if (Characters->GetCharacter(Characters->CHAR_AMRED)->inRange(environment->GetArr(environment->OBJ_LEVER), 8.f))
		{
			Vector3 leverrotation = environment->GetArr(environment->OBJ_LEVER)->GetRotate();

			environment->GetArr(environment->OBJ_LEVER)->SetRotate(Vector3(Math::Clamp(leverrotation.x - Application::yoffset * 0.15f, 0.f, 90.f),
																		   leverrotation.y,
																		   leverrotation.z));
		}
	}
	else
	{
		Vector3 leverrotation = environment->GetArr(environment->OBJ_LEVER)->GetRotate();

		environment->GetArr(environment->OBJ_LEVER)->SetRotate(Vector3(Math::Clamp(leverrotation.x - 0.5f, 0.f, 90.f),
																	   leverrotation.y,
																	   leverrotation.z));
	}

	//Interaction 1 - Button Eject
	{
		text[3]->UpdateTimer(dt);
		//If in range of button
		if (Characters->GetCharacter(Characters->CHAR_AMRED)->inRange(environment->GetArr(environment->OBJ_TABLE1), 10.f))
		{
			text[0]->SetActive(true);
		}
		else
		{
			text[0]->SetActive(false);
		}
		//Button Pressed
		environment->BtnInteract(FallGuys, dt);

		//Ejection Animation
		FallGuys->EjectInteract(&camera2,text[3] , dt);
	}

	//Interaction 2 - Door Open if nearby
	{
		//Door Close
		environment->DoorInteract(environment->OBJ_DOORFRAME1, Characters->GetCharacter(Characters->CHAR_AMRED)->inRange(environment->GetArr(environment->OBJ_DOORFRAME1), 10.f), dt);
		environment->DoorInteract(environment->OBJ_DOORFRAME2, Characters->GetCharacter(Characters->CHAR_AMRED)->inRange(environment->GetArr(environment->OBJ_DOORFRAME2), 10.f), dt);
		environment->DoorInteract(environment->OBJ_DOORFRAME3, Characters->GetCharacter(Characters->CHAR_AMRED)->inRange(environment->GetArr(environment->OBJ_DOORFRAME3), 10.f), dt);
	}

	//Interaction 3 - Murder green dude
	//Disable Tracking
	Characters->GetCharacter(Characters->CHAR_AMGREEN)->SetTarget(Characters->GetCharacter(Characters->CHAR_AMRED));
	
	//Camera mode UI
	Characters->CamChange(camera2, text[2], text[1]);

	//Animation
	Characters->Kill(&camera2, meshlist, dt);

	//Interaction 4 - Bye bye Garbage
	if (environment->GetArr(environment->OBJ_LEVER)->GetRotate().x > 85.f && environment->GetArr(environment->OBJ_GARBAGE)->getActive())
	{
		//move to the other thing :D
		environment->GetArr(environment->OBJ_GARBAGE)->SetInteracted(true);
	}

	if (environment->GetArr(environment->OBJ_GARBAGE)->getInteracted())
	{
		if (environment->GetArr(environment->OBJ_GARBAGE)->GetPos().z > -100)
		{
			Vector3 direction = Vector3(1,0,-1);
			environment->GetArr(environment->OBJ_GARBAGE)->SetTranslate(environment->GetArr(environment->OBJ_GARBAGE)->GetTranslate() + direction  * 5 * dt);

			Vector3 rotate = Vector3(-1, 0, 0);
			environment->GetArr(environment->OBJ_GARBAGE)->SetRotate(environment->GetArr(environment->OBJ_GARBAGE)->GetRotate() + 2 * rotate);

			timepassed += dt;

			if (timepassed > 10.f)
			{
				environment->GetArr(environment->OBJ_GARBAGE)->SetActive(false);
				environment->GetArr(environment->OBJ_GARBAGE)->SetInteracted(false);
			}
		}
	}
}

void SceneText::Render()
{

	renderer->Reset();

	//Camera
	renderer->SetCamera(camera2);
	Axis->Draw(renderer, false);

	//Light
	for (int i = 0; i < 4; i++) 
	{
		renderer->SetLight(lights[i]);
	}
	skybox->Draw(renderer);
	environment->Draw(renderer);

	Characters->DrawAll(renderer, true);
	FallGuys->Draw(renderer, true);
	//Text
	text[4]->Draw(renderer, false);
	text[3]->Draw(renderer, false);
	text[2]->Draw(renderer, false);
	text[1]->Draw(renderer, false);
	text[0]->Draw(renderer, false);

	//On Screen UI
	std::stringstream STRING;
	STRING << "FPS:" << fps;
	text[5]->SetPos(Vector3(0, 0, 0));
	text[5]->SetMode(text[5]->STATIC_SCREENTEXT);
	text[5]->SetText(STRING.str());
	text[5]->Draw(renderer, false);

	STRING.str("");
	STRING << "Press M for Third Person";
	text[5]->SetPos(Vector3(0, 56, 0));
	text[5]->SetMode(text[5]->STATIC_SCREENTEXT);
	text[5]->SetText(STRING.str());
	text[5]->Draw(renderer, false);

	STRING.str("");
	STRING << "Press N for First Person";
	text[5]->SetPos(Vector3(0, 52, 0));
	text[5]->SetMode(text[5]->STATIC_SCREENTEXT);
	text[5]->SetText(STRING.str());
	text[5]->Draw(renderer, false);

	STRING.str("");
	STRING << "Press B for Free View";
	text[5]->SetPos(Vector3(0, 48, 0));
	text[5]->SetMode(text[5]->STATIC_SCREENTEXT);
	text[5]->SetText(STRING.str());
	text[5]->Draw(renderer, false);
}

void SceneText::Exit()
{

}

void SceneText::UpdateMousePos(float xoffset, float yoffset)
{
	camera2.Update(xoffset, yoffset);
}
