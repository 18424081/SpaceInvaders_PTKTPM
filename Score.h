#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Game.h"
#include "DEFINITIONS.h"

class Score
{
private:
	GameDataRef _data;

	int _score1;
	int _score2;

	sf::Text _textScore1;
	sf::Text _textScore2;
	sf::Text _highScore;

	sf::Text _scoreOf1;
	sf::Text _scoreOf2;
	sf::Text _scoreOfHi;

	sf::Text _textLife;

	std::vector<sf::Text> _arrayText;

public:
	Score( GameDataRef data );
	~Score();

	int getScore();
	void UpdateScore( int score1, int score2 );
	void UpdateLife( int life );

	void DrawScore();
};
