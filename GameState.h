#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
//#include "AI.h"

////////////////////////////////////////////////////////////////
//		GameState Class derived State.
//		Define of game.
////////////////////////////////////////////////////////////////

class GameState : public State
{
private:
	/*void InitGridPiece();
	void CheckAndPlacePiece();
	void CheckPlayerHasWon( int turn );
	void Check3PieceForMatch( int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck );*/

	GameDataRef _data;

	sf::Sprite _background;

	sf::Sprite _pauseButton;

	sf::Sprite _gridSprite;

	sf::Sprite _gridPiece[3][3];
	int gridArray[3][3];

	int turn;
	int gameState;

	//AI* ai;

	sf::Clock _clock;
public:
	GameState( GameDataRef data );

	void Init();

	void HandleInput();
	void Update( float dt );
	void Draw( float dt );

};