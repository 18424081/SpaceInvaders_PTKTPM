#pragma once


#include <iostream>

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"
#include "StarryBackground.h"

class MainMenuState : public State
{
private:
	GameDataRef _data;
	sf::Sprite _playButton;
	sf::Sprite _title;
	sf::Sprite _exitButton;

	StarryBackground _background;

public:
	MainMenuState(GameDataRef data);
	~MainMenuState();

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};