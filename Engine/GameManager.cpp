#include "GameManager.h"

GameManager::GameManager()
{

mEngine = new Engine();
mEngine->Initialize("Statki");

mState = State::START;
}

GameManager::~GameManager()
{
	delete mEngine;
}

void GameManager::Start()
{ 
	while (true)
	{
		mEngine->Update();

		switch (mState)
		{
		case State::START:
		{
			
			Sprite testSprite = Sprite("Assets/Art/1.png");

			testSprite.SetScale(1.00f);
			mEngine->beginRender();
			testSprite.Render();
			mEngine->endRender();
			
			if (Keyboard::KeyDown(GLFW_KEY_SPACE) )
			{
				SetState(State::GAMEPLAY);
			}

			
		}
		break;
		case State::GAMEPLAY:
		{
			Sprite testSprite2 = Sprite("Assets/Art/biplane.png");

			testSprite2.SetScale(1.00f);
			mEngine->beginRender();
			testSprite2.Render();
			mEngine->endRender();
		}
		break;
		case State::END:
		{

		}
		break;
		default:
			cout << "Unhandled Game state: " << static_cast<int>(mState) << endl;
		}
		

	}
}
void GameManager::SetState(State state)
{
	mState = state;

	if (mState == State::START)
	{
		mState = state;
	}
}
