#pragma once

#include "SFML/Graphics.hpp"
#include <sstream>
#include <iostream>

#include "DEFINITIONS.h"
#include "Game.h"

class About : public State
{
private:
	GameDataRef _data;

	sf::Sprite _content;
	sf::Sprite _homeButton;

public:
	About( GameDataRef _data );
	~About();

	void Init();
	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};