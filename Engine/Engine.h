#ifndef AZ_ENGINE
#define AZ_ENGINE

#include "GLFW\glfw3.h"
#pragma comment(lib,"opengl32.lib")

#include <iostream>
using namespace std;

class Engine
{
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static double GetDT();


	Engine();
	~Engine();

	bool Initialize(char* windowTitle);

	void Update();
	void beginRender();
	void endRender();

private:
	static GLFWwindow* window;

	//Delta time to have constant buffer
	static double deltaTime;
	double lastTime;
};


#endif 
