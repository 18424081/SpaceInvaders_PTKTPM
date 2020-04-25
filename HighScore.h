#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Game.h"
#include "DEFINITIONS.h"


class HighScore
{
private:
	GameDataRef _data;

	sf::Text _name1;
	sf::Text _score1;
	int _score;
	sf::String _nameSubmit;
	sf::Text _nameTextSm;

	std::vector<sf::Text> _arrayText;

public:
	HighScore( GameDataRef data );
	~HighScore();

	std::pair<std::string, std::string> getSubmit();
	void setScore( int score );
	void UpdateNameToSubmit( std::string name );
	void ShowOnlyHighScore();

	void Init();
	void DrawScore();
	void DrawOnlyHighScore();
};
