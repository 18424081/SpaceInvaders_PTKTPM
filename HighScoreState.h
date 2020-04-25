#pragma once

#include "SFML/Graphics.hpp"
#include <sstream>
#include <iostream>

#include "DEFINITIONS.h"
#include "Game.h"
#include "State.h"
#include "StarryBackground.h"
#include "HighScore.h"

class HighScoreState : public State
{
private:
	GameDataRef _data;

	sf::Sprite _homeButton;
	StarryBackground _background;
	HighScore* _highScore;

public:
	HighScoreState( GameDataRef _data );
	~HighScoreState();

	void Init();
	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};