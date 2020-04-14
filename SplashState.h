#pragma once

#include "SFML/Graphics.hpp"
#include <sstream>
#include <iostream>

#include "DEFINITIONS.h"
#include "Game.h"
#include "State.h"
#include "StarryBackground.h"

class SplashState : public State
{
private:
	GameDataRef _data;
	sf::Clock _clock;
	sf::Sprite _title;
	StarryBackground _background;

public:
	SplashState(GameDataRef _data);
	~SplashState();

	void Init();
	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};