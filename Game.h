#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

////////////////////////////////////////////////////////////////
//		GAME CLASS
//		
////////////////////////////////////////////////////////////////

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager asset;
	InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
private:
	const float dt = 1.0f / 60.0f;
	sf::Clock _clock;

	GameDataRef _data = std::make_shared<GameData>();

	void Run();
	void RunTest();

public:
	Game( int width, int height, std::string title );
};