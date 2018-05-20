#include "Engine\Engine.h"
#include "Engine\Graphics\Sprite.h"
#include <iostream>
using namespace std;

int main()
{
	Engine engine;
	engine.Initialize("TEST");

	Sprite testSprite = Sprite("Assets/Art/Biplane.png", -100, -100);

	while (true)
	{
		engine.Update();
		testSprite.Update();

		engine.beginRender();
		testSprite.Render();
		engine.endRender();
	}
	return 0;
}
