#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "shader.hpp"
#include "SceneManager.h"

#include <iostream>

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

bool firstMouse = true;

bool Application::bQuit = false;
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
	if (Application::Cursor_Off)
	{
		Application::FOV -= (float)yoffset;
		if (Application::FOV < 1.0f)
			Application::FOV = 1.0f;
		if (Application::FOV > 45.0f)
			Application::FOV = 45.0f;
	}
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
	m_window = glfwCreateWindow(m_width, m_height, "Group 9 Studio Project 2", NULL, NULL);
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
	//DisableCursor();
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
	//Main Loop
	//PLEASE REMEMBER TO REPLACE TESTING SCENES ONCE DONE
	SceneManager* sceneManager = new SceneManager();
	//sceneManager->Init(SceneManager::SCENE_STADIUM);
	sceneManager->Init(SceneManager::SCENE_MAINMENU); 

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !bQuit)
	{
		sceneManager->Update(&m_timer);
		Application::xoffset = 0;
		Application::yoffset = 0;

		sceneManager->Render();

		if (IsKeyPressed(VK_F1))
		{
			sceneManager->ChangeScene(SceneManager::SCENE_CITY);
		}
		if (IsKeyPressed(VK_F2))
		{
			sceneManager->ChangeScene(SceneManager::SCENE_LIBRARY);
		}
		if (IsKeyPressed(VK_F3))
		{
			sceneManager->ChangeScene(SceneManager::SCENE_TRAIN);
		}
		if (IsKeyPressed(VK_F4))
		{
			sceneManager->ChangeScene(SceneManager::SCENE_STADIUM);
		}
		if (IsKeyPressed(VK_F6))
		{
			sceneManager->ChangeScene(SceneManager::SCENE_HALL);
		}
		if (IsKeyPressed(VK_F7))
		{
			sceneManager->ChangeScene(SceneManager::SCENE_GAMEOVER);
		}
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   
	} //Check if the ESC key had been pressed or if the window had been closed
	delete sceneManager;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

