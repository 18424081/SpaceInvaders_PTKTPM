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
	IncludePlayerNInvader* _includePlayerNInvader;
	
    bool _isGameover;
	bool _isGameWin;

public:
	GameState( GameDataRef data );
	~GameState( );

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );
};
