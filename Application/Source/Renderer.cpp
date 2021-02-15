#include "Renderer.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Application.h"

Renderer::Renderer() :
	m_vertexArrayID(0)
{
	//Load Vertex and fragment shaders
	programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); //Set BG colour
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	

	//Parameters
	Parameters[U_MVP] = glGetUniformLocation(programID, "MVP");
	Parameters[U_MODELVIEW] = glGetUniformLocation(programID, "MV");
	Parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(programID, "MV_inverse_transpose");
	Parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(programID, "material.kAmbient");
	Parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(programID, "material.kDiffuse");
	Parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(programID, "material.kSpecular");
	Parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(programID, "material.kShininess");
	Mesh::SetMaterialLoc(Parameters[U_MATERIAL_AMBIENT], Parameters[U_MATERIAL_DIFFUSE], Parameters[U_MATERIAL_SPECULAR], Parameters[U_MATERIAL_SHININESS]);
	Parameters[U_LIGHTENABLED] = glGetUniformLocation(programID, "lightEnabled");

	Parameters[U_NUMLIGHTS] = glGetUniformLocation(programID, "numLights");

	// Get a handle for our "colorTexture" uniform
	Parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(programID, "colorTextureEnabled");
	Parameters[U_COLOR_TEXTURE] = glGetUniformLocation(programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	Parameters[U_TEXT_ENABLED] = glGetUniformLocation(programID, "textEnabled");
	Parameters[U_TEXT_COLOR] = glGetUniformLocation(programID, "textColor");
	
	glUseProgram(programID);
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(Parameters[U_NUMLIGHTS], 5);

}

Renderer::~Renderer()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(programID);
}

void Renderer::Reset()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	modelStack.LoadIdentity();
}

void Renderer::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(Parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(Parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight)
	{
		glUniform1i(Parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(Parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(Parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(Parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(Parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(Parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(Parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(Parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Renderer::RenderText(Mesh* mesh, std::string text, Color color, int textdataArray[])
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glUniform1i(Parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(Parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(Parameters[U_LIGHTENABLED], 0);
	glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(Parameters[U_COLOR_TEXTURE], 0);

	float accumulator = 0.f;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToIdentity();
		characterSpacing.SetToTranslation(accumulator, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(Parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		accumulator += textdataArray[text[i]] / 128.0f + textdataArray[text[i + 1]] / 128.0f;

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(Parameters[U_TEXT_ENABLED], 0);

}

void Renderer::RenderDialogue(Mesh* mesh, std::string text, Color color, int textdataArray[], int index)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glUniform1i(Parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(Parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(Parameters[U_LIGHTENABLED], 0);
	glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(Parameters[U_COLOR_TEXTURE], 0);

	float accumulator = 0.f;
	if (index > text.length())
	{
		index = text.length();
	}
	for (unsigned i = 0; i < index; ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToIdentity();
		characterSpacing.SetToTranslation(accumulator, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(Parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		accumulator += textdataArray[text[i]] / 128.0f + textdataArray[text[i + 1]] / 128.0f;
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(Parameters[U_TEXT_ENABLED], 0);
}

void Renderer::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int textdataArray[])
{

	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);

	glUniform1i(Parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(Parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(Parameters[U_LIGHTENABLED], 0);
	glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(Parameters[U_COLOR_TEXTURE], 0);

	float accumulator = 0.f;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;

		//Change this line inside for loop
		characterSpacing.SetToTranslation(0.5f + accumulator, 0.5f, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(Parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);

		accumulator += textdataArray[text[i]] / 128.0f + textdataArray[text[i + 1]] / 128.0f;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(Parameters[U_TEXT_ENABLED], 0);

	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void Renderer::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly remove rotate for something else lul later
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 0);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Renderer::AddTransformation(Vector3 Translate, Vector3 Pos, Vector3 Rotation, Vector3 Scale)
{
	modelStack.Translate(Pos.x, Pos.y, Pos.z);
	modelStack.Translate(Translate.x, Translate.y, Translate.z);
	modelStack.Rotate(Rotation.y, 0, 1, 0);
	modelStack.Rotate(Rotation.x, 1, 0, 0);
	modelStack.Rotate(Rotation.z, 0, 0, 1);
	modelStack.Scale(Scale.x, Scale.y, Scale.z);
}

void Renderer::AddTranslate(float x, float y, float z)
{
	modelStack.Translate(x, y, z);
}

void Renderer::AddRotate(float x, float y, float z)
{
	modelStack.Rotate(x, 1, 0, 0);
	modelStack.Rotate(y, 0, 1, 0);
	modelStack.Rotate(z, 0, 0, 1);
}

void Renderer::AddScale(float x, float y, float z)
{
	modelStack.Scale(x, y, z);
}

void Renderer::AddTransformation(Vector3 Translate, Vector3 Pos, Vector3 Rotation, Vector3 Scale, Vector3 PivotRotate)
{
	modelStack.Translate(Pos.x, Pos.y, Pos.z);
	modelStack.Translate(Translate.x, Translate.y, Translate.z);
	modelStack.Rotate(Rotation.y, 0, 1, 0);
	modelStack.Rotate(Rotation.x, 1, 0, 0);
	modelStack.Rotate(Rotation.z, 0, 0, 1);
	modelStack.Translate(0, (Pos.y + Translate.y) * -1, 0);
	modelStack.Rotate(PivotRotate.x, 1, 0, 0);
	modelStack.Rotate(PivotRotate.y, 0, 1, 0);
	modelStack.Rotate(PivotRotate.z, 0, 0, 1);
	modelStack.Translate(0, (Pos.y + Translate.y), 0);
	modelStack.Scale(Scale.x, Scale.y, Scale.z);
}

void Renderer::PushTransform()
{
	modelStack.PushMatrix();
}

void Renderer::PopTransform()
{
	modelStack.PopMatrix();
}

void Renderer::SetCamera(CameraVer2 camera)
{
	//viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	viewStack.LookAt(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z, 
				     camera.GetPosition().x + camera.GetView().x, camera.GetPosition().y + camera.GetView().y, camera.GetPosition().z + camera.GetView().z,
					 camera.GetUp().x, camera.GetUp().y, camera.GetUp().z);
	Mtx44 projection;
	projection.SetToPerspective(Application::FOV, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
}

void Renderer::SetLight(Light* light)
{
	if (light->type == light->LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir = light->position;
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(light-> parameters[light->U_LIGHT_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light->type == light->LIGHT_SPOT)
	{
		Vector3 lightPosition_cameraspace = viewStack.Top() * light->position;
		glUniform3fv(light->parameters[light->U_LIGHT_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light->spotDirection;
		glUniform3fv(light->parameters[light->U_LIGHT_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Vector3 lightPosition_cameraspace = viewStack.Top() * light->position;
		glUniform3fv(light->parameters[light->U_LIGHT_POSITION], 1, &lightPosition_cameraspace.x);
	}
}

unsigned Renderer::GetprogramID()
{
	return programID;
}
