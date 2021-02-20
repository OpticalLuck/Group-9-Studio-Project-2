#include "Renderer.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Application.h"
#include <sstream>
Renderer::Renderer(int numlight)
{
	//Load Vertex and fragment shaders
	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 1000.f);
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
	Parameters[U_MVP] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "MVP");
	Parameters[U_MODELVIEW] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "MV");
	Parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "MV_inverse_transpose");
	Parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "material.kAmbient");
	Parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "material.kDiffuse");
	Parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "material.kSpecular");
	Parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "material.kShininess");

	Parameters[U_MATERIAL_MAPKD] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "material.map_Kd");
	Parameters[U_MATERIAL_MAPKD_ENABLED] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "diffuseMapEnabled");

	Mesh::SetMaterialLoc(Parameters[U_MATERIAL_AMBIENT], Parameters[U_MATERIAL_DIFFUSE], Parameters[U_MATERIAL_SPECULAR], Parameters[U_MATERIAL_SHININESS], Parameters[U_MATERIAL_MAPKD], Parameters[U_MATERIAL_MAPKD_ENABLED]);
	Parameters[U_LIGHTENABLED] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "lightEnabled");
	Parameters[U_NUMLIGHTS] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "numLights");

	// Get a handle for our "colorTexture" uniform
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		std::stringstream ss;
		ss.str("");
		ss << "colorTextureEnabled[" << i << "]";
		Parameters[U_COLOR_TEXTURE_ENABLED + i] = glGetUniformLocation(Shader::GetInstance()->shaderdata, ss.str().c_str());
	
		ss.str("");
		ss << "colorTexture[" << i << "]";
		Parameters[U_COLOR_TEXTURE + i] = glGetUniformLocation(Shader::GetInstance()->shaderdata, ss.str().c_str());
	}

	// Get a handle for our "textColor" uniform
	Parameters[U_TEXT_ENABLED] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "textEnabled");
	Parameters[U_TEXT_COLOR] = glGetUniformLocation(Shader::GetInstance()->shaderdata, "textColor");
	
	glUseProgram(Shader::GetInstance()->shaderdata);
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(Parameters[U_NUMLIGHTS], numlight);

}

Renderer::~Renderer()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(Shader::GetInstance()->shaderdata);
}

void Renderer::Reset()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		glUniform1f(Parameters[U_MATERIAL_MAPKD_ENABLED], 0);
		glUniform1f(Parameters[U_MATERIAL_MAPKD], 0);
	}
	else
	{
		glUniform1i(Parameters[U_LIGHTENABLED], 0);
	}

	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (mesh->textureArr[i] > 0)
		{
			glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArr[i]);
			glUniform1i(Parameters[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}


	mesh->Render();

	if (mesh->textureArr[0] > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Renderer::RenderText(Mesh* mesh, std::string text, Color color, int textdataArray[])
{
	if (!mesh || mesh->textureArr[0] <= 0) //Proper error check
		return;

	glUniform1i(Parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(Parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(Parameters[U_LIGHTENABLED], 0);
	glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArr[0]);
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
	if (!mesh || mesh->textureArr[0] <= 0) //Proper error check
		return;

	glUniform1i(Parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(Parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(Parameters[U_LIGHTENABLED], 0);
	glUniform1i(Parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArr[0]);
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

	if (!mesh || mesh->textureArr[0] <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 128, 0, 72, -10, 10); //size of screen UI
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
	glBindTexture(GL_TEXTURE_2D, mesh->textureArr[0]);
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

void Renderer::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 128, 0, 72, -10, 10); //size of screen UI
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

void Renderer::AddTransformation(Vector3 Translate, Vector3 Rotation, Vector3 Scale)
{
	modelStack.Translate(Translate.x, Translate.y, Translate.z);
	modelStack.Rotate(Rotation.z, 0, 0, 1);
	modelStack.Rotate(Rotation.y, 0, 1, 0);
	modelStack.Rotate(Rotation.x, 1, 0, 0);
	modelStack.Scale(Scale.x, Scale.y, Scale.z);
}

void Renderer::AddTranslate(float x, float y, float z)
{
	modelStack.Translate(x, y, z);
}

void Renderer::AddRotate(float x, float y, float z)
{
	modelStack.Rotate(z, 0, 0, 1);
	modelStack.Rotate(y, 0, 1, 0);
	modelStack.Rotate(x, 1, 0, 0);
}

void Renderer::AddScale(float x, float y, float z)
{
	modelStack.Scale(x, y, z);
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
	Vector3 Target = camera.GetView() + camera.GetPosition();
	viewStack.LookAt(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z, 
					Target.x, Target.y, Target.z,
					camera.GetUp().x, camera.GetUp().y, camera.GetUp().z);
	Mtx44 projection;
	projection.SetToPerspective(Application::FOV, 16.f / 9.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
}

void Renderer::SetLight(Light* light, CameraVer2 camera)
{
	if (light->type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir = light->position;
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(light->parameters[Light::U_LIGHT_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light->type == Light::LIGHT_SPOT)
	{
		Vector3 lightPosition_cameraspace = viewStack.Top() * (light->position - camera.GetPosition()) ;
		glUniform3fv(light->parameters[Light::U_LIGHT_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light->spotDirection;
		glUniform3fv(light->parameters[Light::U_LIGHT_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Vector3 lightPosition_cameraspace = viewStack.Top() * light->position;
		glUniform3fv(light->parameters[Light::U_LIGHT_POSITION], 1, &lightPosition_cameraspace.x);
	}
}

void Renderer::LoadIdentity()
{
	viewStack.LoadIdentity();
	modelStack.LoadIdentity();
}

unsigned Renderer::GetprogramID()
{
	return Shader::GetInstance()->shaderdata;
}
