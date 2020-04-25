#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "DEFINITIONS.h"
#include "StarryBackground.h"

class PauseState : public State
{
private:
	GameDataRef _data;

	StarryBackground _background;

	sf::Sprite _resumeButton;
	sf::Sprite _homeButton;
public:
	PauseState( GameDataRef data );

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};
