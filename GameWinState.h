#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "DEFINITIONS.h"
#include "StarryBackground.h"
#include "HighScore.h"

class GameWinState : public State
{
private:
	GameDataRef _data;
	HighScore* _highSc;

	StarryBackground _background;

	int _score;
	sf::Sprite _resumeButton;
	sf::Sprite _homeButton;
	sf::Sprite _submit;
	sf::Sprite _title;
	sf::String _nameSubmit;

public:
	GameWinState( GameDataRef data, int score );
	~GameWinState();

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};
