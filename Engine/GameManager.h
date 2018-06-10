#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "Engine.h"
#include "Graphics\Sprite.h"
#include "IO\Keyboard.h"

class GameManager
{
public:
	enum class State
	{
		START,
		GAMEPLAY,
		END,
	};
public:
	GameManager();
	~GameManager();
	void Start();
private:
	void SetState(State state);
private:
	Engine* mEngine;
	State mState;
	Sprite mStartSprite;
};

#endif // !GAME_MANAGER
