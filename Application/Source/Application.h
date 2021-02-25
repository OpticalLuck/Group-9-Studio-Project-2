
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double* xpos, double* ypos);
	static void EnableCursor();
	static void DisableCursor();
	static int GetWindowWidth();
	static int GetWindowHeight();
	
	static bool bQuit;
	static bool Cursor_Off;
	static unsigned m_width;
	static unsigned m_height;
	static float FOV;

	static double xoffset;
	static double yoffset;
private:

	//Declare a window object
	StopWatch m_timer;
};

#endif