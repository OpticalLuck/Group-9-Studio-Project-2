#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneCity.h"

//TODO!! REMOVE TESTING SCENES
//#include "SceneNPCTest.h"
//#include "SceneTest.h"

#include "shader.hpp"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

bool firstMouse = true;
bool Application::Cursor_Off = false;
unsigned Application::m_width;
unsigned Application::m_height;
float lastX = 640, lastY = 360; //Middle of screen
float Application::FOV = 45;

double Application::xoffset = 0;
double Application::yoffset = 0;


//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool Application::IsMousePressed(unsigned short key)
{
	return glfwGetMouseButton(m_window, key) != 0;
}

void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}

void Application::EnableCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	Cursor_Off = false;
}

void Application::DisableCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	firstMouse = true;
	Cursor_Off = true;
}

int Application::GetWindowWidth()
{
	return m_width;
}

int Application::GetWindowHeight()
{
	return m_height;
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	Application::m_width = w;
	Application::m_height = h;
	glViewport(0, 0, w, h);
	 
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (Application::Cursor_Off)
	{
		if (firstMouse) // initially set to true
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		Application::xoffset += xpos - lastX;
		Application::yoffset += lastY - ypos;

		lastX = xpos;
		lastY = ypos;
	}
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application::FOV -= (float)yoffset;
	if (Application::FOV < 1.0f)
		Application::FOV = 1.0f;
	if (Application::FOV > 45.0f)
		Application::FOV = 45.0f;
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_width = 1280;
	m_height = 720;
	m_window = glfwCreateWindow(m_width, m_height, "Test Window", NULL, NULL);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	//Sets the mouse callback
	DisableCursor();
	glfwSetCursorPosCallback(m_window, mouse_callback);
	glfwSetScrollCallback(m_window, scroll_callback);
	

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	
	Shader::GetInstance()->shaderdata = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	//Main Loop
	//PLEASE REMEMBER TO REPLACE TESTING SCENES ONCE DONE
	Scene* scene1 = new SceneCity();
	scene1->Init();
	Scene* scene2 = nullptr;
	//scene2->Init();
	Scene* scene3 = nullptr;
	//scene3->Init();
	Scene* scene4 = nullptr;
	Scene* scene5 = nullptr;

	Scene* scene = scene1;
	scene->InitGL();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{

		scene->UpdateMousePos(Application::xoffset, Application::yoffset);
		scene->Update(m_timer.getElapsedTime());
		Application::xoffset = 0;
		Application::yoffset = 0;
		scene->Render();

		if (IsKeyPressed(VK_F1))
		{
			if (scene != scene2 && scene2)
			{
			//Change to Scene2
			scene->Exit();
			scene = scene2;
			scene->InitGL();
			}
		}
		if (IsKeyPressed(VK_F2))
		{
			if (scene != scene1 && scene1)
			{
				//Change to Scene1
				scene->Exit();
				scene = scene1;
				scene->InitGL();
			}
		}
		if (IsKeyPressed(VK_F3))
		{
			if (scene != scene3 && scene3)
			{
				//Change to Scene1
				scene->Exit();
				scene = scene3;
				scene->InitGL();
			}
		}

		//Swap buffers
		glfwSwapBuffers(m_window);

		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene1;
	//delete scene2;
	//delete scene3;
	//delete scene4;
	//delete scene5;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

