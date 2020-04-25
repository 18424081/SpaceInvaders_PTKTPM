#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "DEFINITIONS.h"
#include "StarryBackground.h"
#include "HighScore.h"

class GameOverState : public State
{
private:
	GameDataRef _data;

	StarryBackground _background;

	sf::Sprite _retryButton;
	sf::Sprite _homeButton;
	sf::Sprite _title;
public:
	GameOverState( GameDataRef data );

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};
