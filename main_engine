#include "Engine\Engine.h"
#include "Engine\Graphics\Sprite.h"
#include "Engine\IO\Mouse.h"
#include <iostream>
using namespace std;

int main()
{
	Engine engine;
	engine.Initialize("TEST");

	//Path and Pos
	Sprite testSprite = Sprite("Assets/Art/Biplane.png", 0, 0);
	//Scale of Image
	testSprite.SetScale(0.25f);
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
