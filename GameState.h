#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "State.h"
#include "Game.h"
#include "GameOverState.h"
#include "GameWinState.h"
#include "PauseState.h"
#include "DEFINITIONS.h"
#include "Score.h"
#include "InvaderManager.h"
#include "Player.h"
#include "IncludePlayerNInvader.h"
//#include "AI.h"

////////////////////////////////////////////////////////////////
//		GameState Class derived State.
//		Define of game.
////////////////////////////////////////////////////////////////

class GameState : public State
{
private:
    GameDataRef _data;

	Score* _score;
	/*InvaderManager* _invaderManager;
	Player* _player;*/
	IncludePlayerNInvader* _includePlayerNInvader;
	
	int flagIcon1 = 1;
    int m_score = 0;
    bool _isGameover;
	bool _isGameWin;
    sf::Clock m_gameOverClock;
	sf::Clock _clock;

	sf::Sprite _playerIcon;

public:
	GameState( GameDataRef data );
	~GameState( );

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};
