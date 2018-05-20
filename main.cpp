#include "Engine\Engine.h"
#include <iostream>

using namespace std;

int main()
{
	Engine engine;
	engine.Initialize("TEST");

	while (true)
	{
		engine.Update();
		engine.Render();
	}
	return 0;
}
