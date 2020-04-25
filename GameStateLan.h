#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "State.h"
#include "Game.h"
#include "PauseState.h"
#include "DEFINITIONS.h"
#include "Score.h"
#include "InvaderManager.h"
#include "Player.h"
#include "IncludePlayerNInvader.h"

////////////////////////////////////////////////////////////////
//		GameState Class derived State.
//		Define of game.
////////////////////////////////////////////////////////////////

class GameStateLan : public State
{
private:
	GameDataRef _data;

	Score* _score;
	IncludePlayerNInvader* _includePlayerNInvader;

	int flagIcon1 = 1;
	int m_score = 0;
	bool m_isGameover;
	sf::Clock m_gameOverClock;
	sf::Clock _clock;

	sf::Sprite _playerIcon;

public:
	GameStateLan( GameDataRef data );
	~GameStateLan();

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};

