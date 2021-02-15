#include "A1FG.h"
#include "MeshBuilder.h"

A1FG::A1FG()
{
	SetPos(Vector3(0, 3.5f, -8));
	{
	BodyArr[TOP_BODY] = MeshBuilder::GenerateHemisphere("Hemisphere", Color(1.f, 0.41f, 0.75f), 50, 50, 1.f, true);
	BodyArr[TOP_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[TOP_BODY]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[TOP_BODY]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[TOP_BODY]->material.kShininess = 1.f;
	
	BodyArr[BODY] = MeshBuilder::GenerateCylinder("Body", Color(1.f, 0.41f, 0.79f), 20, 2, 1.f, false);
	BodyArr[BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[BODY]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[BODY]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[BODY]->material.kShininess = 1.f;

	BodyArr[BOTTOM_BODY] = MeshBuilder::GenerateHemisphere("Hemisphere", Color(1.f, 0.41f, 0.75f), 50, 50, 1.f, true);
	BodyArr[BOTTOM_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[BOTTOM_BODY]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[BOTTOM_BODY]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[BOTTOM_BODY]->material.kShininess = 1.f;
	}

	BodyArr[FACE] = MeshBuilder::GenerateSphere("FACE", Color(1, 1, 1), 50, 50, 1);
	BodyArr[FACE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[FACE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[FACE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[FACE]->material.kShininess = 1.f;
	

	BodyArr[EYE] = MeshBuilder::GenerateSphere("EYE", Color(0, 0, 0), 50, 50, 1);
	BodyArr[EYE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[EYE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[EYE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[EYE]->material.kShininess = 1.f;

	BodyArr[SHOULDER] = MeshBuilder::GenerateSphere("Sphere", Color(1.f, 0.41f, 0.79f), 20, 35, 1.f);
	BodyArr[SHOULDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[SHOULDER]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[SHOULDER]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[SHOULDER]->material.kShininess = 1.f;

	BodyArr[UPPER_ARM] = MeshBuilder::GenerateCylinder("Cylinder", Color(1.f, 0.41f, 0.79f), 20, 2, 1.f, false);
	BodyArr[UPPER_ARM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[UPPER_ARM]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[UPPER_ARM]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[UPPER_ARM]->material.kShininess = 1.f;

	BodyArr[ELBOW] = MeshBuilder::GenerateSphere("Sphere", Color(1.f, 0.41f, 0.79f), 20, 35, 1.f);
	BodyArr[ELBOW]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[ELBOW]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[ELBOW]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[ELBOW]->material.kShininess = 1.f;

	BodyArr[LOWER_ARM] = MeshBuilder::GenerateCylinder("Cylinder", Color(1.f, 0.41f, 0.79f), 20, 2, 1.f, false);
	BodyArr[LOWER_ARM]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[LOWER_ARM]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[LOWER_ARM]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[LOWER_ARM]->material.kShininess = 1.f;

	BodyArr[LEG] = MeshBuilder::GenConeFrust("LEG", Color(1.f, 0.41f, 0.79f), 1, 2.f, 1.f, Position(0, 0, 0), 0.75f, false);
	BodyArr[LEG]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[LEG]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[LEG]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[LEG]->material.kShininess = 1.f;

	BodyArr[FEET] = MeshBuilder::GenConeFrust("FEET", Color(1.f, 0.41f, 0.79f), 1, 2.5f, 0.f, Position(0, 0, -0.75f), 1, false);
	BodyArr[FEET]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	BodyArr[FEET]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	BodyArr[FEET]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	BodyArr[FEET]->material.kShininess = 1.f;
}

A1FG::~A1FG()
{
}

void A1FG::Draw(Renderer* renderer, bool enablelight)
{//-----------------------Body------------------------//
	if(getActive())
	{
		{
			renderer->PushTransform();
			renderer->AddTranslate(GetPos().x, GetPos().y, GetPos().z);
			renderer->AddTranslate(0, GetPos().y * -0.5f, 0);
			renderer->AddRotate(GetRotate().x, GetRotate().y, GetRotate().z);
			renderer->AddTranslate(0, GetPos().y * 0.5f, 0);
			renderer->RenderMesh(BodyArr[TOP_BODY], true);

			renderer->PushTransform();
			renderer->AddTranslate(0, -1, 0);
			renderer->AddScale(1, 1, 1);
			renderer->RenderMesh(BodyArr[BODY], true);

			renderer->PushTransform();
			renderer->AddTranslate(0, -1, 0);
			renderer->AddRotate(180, 0, 0);
			renderer->AddScale(1, 1, 1);
			renderer->RenderMesh(BodyArr[BOTTOM_BODY], true);
			renderer->PopTransform();


			renderer->PushTransform();
			renderer->AddTranslate(0, 0.8f, 0.8f);
			renderer->AddScale(0.7f, 0.7f, 0.7f);
			renderer->AddScale(1, 1, 0.5f);
			renderer->RenderMesh(BodyArr[FACE], true);

			renderer->PushTransform();
			renderer->AddTranslate(0.4f, -0.2f, 0.8f);
			renderer->AddScale(0.25f, 0.25f, 0.25f);
			renderer->AddScale(0.5f, 1, 1);
			renderer->RenderMesh(BodyArr[EYE], true);
			renderer->PopTransform();

			renderer->PushTransform();
			renderer->AddTranslate(-0.4f, -0.2f, 0.8f);
			renderer->AddScale(0.25f, 0.25f, 0.25f);
			renderer->AddScale(0.5f, 1, 1);
			renderer->RenderMesh(BodyArr[EYE], true);
			renderer->PopTransform();
			renderer->PopTransform();
			renderer->PopTransform();
		}
		//----------------------/Body------------------------//

		//-----------------------Arms------------------------//
		{
		////Left
		renderer->PushTransform();
		renderer->AddTranslate(1, -0.5f, 0.2f);
		renderer->AddRotate(0, 0, 20);
		renderer->AddScale(0.3f, 0.3f, 0.3f);
		renderer->RenderMesh(BodyArr[SHOULDER], true);

		renderer->PushTransform();
		renderer->AddTranslate(0, -2, 0);
		renderer->AddScale(1, 2, 1);
		renderer->RenderMesh(BodyArr[UPPER_ARM], true);

		renderer->PushTransform();
		renderer->AddScale(1, 0.5f, 1);
		renderer->AddTranslate(0, 2, 0);
		renderer->AddTranslate(0, -4, 0);
		renderer->AddRotate(0, 0, -20);
		renderer->RenderMesh(BodyArr[ELBOW], true);

		renderer->PushTransform();
		renderer->AddTranslate(0, -2, 0);
		renderer->AddScale(1, 2, 1);
		renderer->RenderMesh(BodyArr[LOWER_ARM], true);
		renderer->PopTransform();
		renderer->PopTransform();
		renderer->PopTransform();
		renderer->PopTransform();

		//RIGHT
		renderer->PushTransform();
		renderer->AddTranslate(-1, -0.5f, 0.2f);
		renderer->AddRotate(0, 0, -20);
		renderer->AddScale(0.3f, 0.3f, 0.3f);
		renderer->RenderMesh(BodyArr[SHOULDER], true);

		renderer->PushTransform();
		renderer->AddTranslate(0, -2, 0);
		renderer->AddScale(1, 2, 1);
		renderer->RenderMesh(BodyArr[UPPER_ARM], true);

		renderer->PushTransform();
		renderer->AddScale(1, 0.5f, 1);
		renderer->AddTranslate(0, 2, 0);
		renderer->AddTranslate(0, -4, 0);
		renderer->AddRotate(0, 0, 20);
		renderer->RenderMesh(BodyArr[ELBOW], true);

		renderer->PushTransform();
		renderer->AddTranslate(0, -2, 0);
		renderer->AddScale(1, 2, 1);
		renderer->RenderMesh(BodyArr[LOWER_ARM], true);

		renderer->PopTransform();
		renderer->PopTransform();
		renderer->PopTransform();
		renderer->PopTransform();
	}
		//----------------------/Arms------------------------//

		//-----------------------Legs------------------------//
		{
		//Left
		renderer->PushTransform();
		renderer->AddTranslate(0.4f, -2.8f, 0);
		renderer->AddScale(0.2f, 0.2f, 0.2f);

		renderer->AddTranslate(0, -1.f, 0);
		renderer->AddScale(1, 1.1f, 1);
		renderer->RenderMesh(BodyArr[LEG], true);

		renderer->PushTransform();
		renderer->AddTranslate(0, -0.3f, 1.4f);
		renderer->AddScale(0.9f, 1.f, 2); //stretching
		renderer->AddScale(1, 0.5f, 1); //scale back height from cylinder
		renderer->AddScale(1.5f, 1.5f, 1.5f); //uniform scale
		renderer->RenderMesh(BodyArr[FEET], true);
		renderer->PopTransform();
		renderer->PopTransform();

		//Right
		renderer->PushTransform();
		renderer->AddTranslate(-0.4f, -2.8f, 0);
		renderer->AddScale(0.2f, 0.2f, 0.2f);

		renderer->AddTranslate(0, -1.f, 0);
		renderer->AddScale(1, 1.1f, 1);
		renderer->RenderMesh(BodyArr[LEG], true);

		renderer->PushTransform();
		renderer->AddTranslate(0, -0.3f, 1.4f);
		renderer->AddScale(0.9f, 1.f, 2); //stretching
		renderer->AddScale(1, 0.5f, 1); //scale back height from cylinder
		renderer->AddScale(1.5f, 1.5f, 1.5f); //uniform scale
		renderer->RenderMesh(BodyArr[FEET], true);

		renderer->PopTransform();
		renderer->PopTransform();
	}
		//----------------------/Legs------------------------//
		renderer->PopTransform();
	}
}

void A1FG::EjectInteract(CameraVer2* camera, Text* text, double dt)
{
	if (getInteracted() && getActive())
	{
		SetPos(Vector3(-15, 3, -46));
		camera->ToggleMode(camera->FIRST_PERSON);
		camera->ToggleControls(false);
		camera->SetPosition(Vector3(0, 5, -15));
		camera->SetView(Vector3(0, 0, -1));

		if (GetPos().x < 30.f)
		{
			float x_change = GetTranslate().x + 10 * dt;
			SetTranslate(Vector3(x_change, 0, 0));

			float RotationZ = GetRotate().z - 5;
			SetRotate(Vector3(0, 0, RotationZ));

			if (GetPos().x > -5.f)
			{
				text->StartTimer();
			}
		}
		else
		{
			camera->SetPosition(Vector3(0, 3, 8));
			camera->ToggleMode(camera->GetPrevMode());
			camera->ToggleControls(true);
			SetActive(false);
			SetInteracted(false);
			text->SetActive(false);
		}
	}
}

