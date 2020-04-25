#include "Score.h"

Score::Score( GameDataRef data ) : _data( data )
{
	// Title.
	_textScore1.setString( "SCORE P1" );
	_textScore1.setFont( _data->asset.GetFont( "arcade" ) );
	_textScore1.setFillColor( sf::Color::White );
	_textScore1.setOutlineColor( sf::Color::Black );
	_textScore1.setCharacterSize( 25 );
	_textScore1.setPosition( 50, 10 - _textScore1.getGlobalBounds().height / 2 );

	_textScore2.setString( "SCORE P2" );
	_textScore2.setFont( _data->asset.GetFont( "arcade" ) );
	_textScore2.setFillColor( sf::Color::White );
	_textScore2.setOutlineColor( sf::Color::Black );
	_textScore2.setCharacterSize( 25 );
	_textScore2.setPosition( 850, 10 - _textScore1.getGlobalBounds().height / 2 );

	_highScore.setString( "HIGHSCORE" );
	_highScore.setFont( _data->asset.GetFont( "arcade" ) );
	_highScore.setFillColor( sf::Color::White );
	_highScore.setOutlineColor( sf::Color::Black );
	_highScore.setCharacterSize( 25 );
	_highScore.setPosition( ( SCREEN_WIDTH / 2 ) - ( _highScore.getGlobalBounds().width / 2 )
		, 10 - ( _highScore.getGlobalBounds().height / 2 ) );

	// Show Point.

	_scoreOf1.setFont( _data->asset.GetFont( "arcade" ) );
	_scoreOf1.setFillColor( sf::Color::White );
	_scoreOf1.setOutlineColor( sf::Color::Black );
	_scoreOf1.setCharacterSize( 30 );
	_scoreOf1.setPosition( 50, 30 - _textScore1.getGlobalBounds().height / 2 );


	_scoreOf2.setFont( _data->asset.GetFont( "arcade" ) );
	_scoreOf2.setFillColor( sf::Color::White );
	_scoreOf2.setOutlineColor( sf::Color::Black );
	_scoreOf2.setCharacterSize( 30 );
	_scoreOf2.setPosition( 850, 30 - _textScore1.getGlobalBounds().height / 2 );


	_scoreOfHi.setFont( _data->asset.GetFont( "arcade" ) );
	_scoreOfHi.setFillColor( sf::Color::White );
	_scoreOfHi.setOutlineColor( sf::Color::Black );
	_scoreOfHi.setCharacterSize( 30 );
	_scoreOfHi.setPosition( ( SCREEN_WIDTH / 2 ) - ( _scoreOfHi.getGlobalBounds().width / 2 )
		, 30 - ( _scoreOfHi.getGlobalBounds().height / 2 ) );

	// Show life.
	_textLife.setString( "3 LIFE" );
	_textLife.setFont( _data->asset.GetFont( "arcade" ) );
	_textLife.setFillColor( sf::Color::White );
	_textLife.setOutlineColor( sf::Color::Black );
	_textLife.setCharacterSize( 25 );
	_textLife.setPosition( 200, 10 - _textScore1.getGlobalBounds().height / 2 );

	/*_textScore2.setString( "<SCORE P2>" );
	_textScore2.setFont( _data->asset.GetFont( "arcade" ) );
	_textScore2.setFillColor( sf::Color::White );
	_textScore2.setOutlineColor( sf::Color::Black );
	_textScore2.setCharacterSize( 25 );
	_textScore2.setPosition( 850, 10 - _textScore1.getGlobalBounds().height / 2 );*/

	UpdateScore( 0, 0 );
}

Score::~Score()
{

}

int Score::getScore()
{
	return _score1;
}

void Score::UpdateScore( int score1, int score2 )
{
	_score1 = score1;
	int hi = ( score1 > score2 ) ? score1 : score2;
	std::string hiScore = std::to_string( hi );
	std::string sc1 = std::to_string( score1 );
	std::string sc2 = std::to_string( score2 );

	if ( score1 < 10 )
		sc1 = "000" + sc1;
	else if ( score1 < 100 )
		sc1 = "00" + sc1;
	else if ( score1 < 1000 )
		sc1 = "0" + sc1;

	if ( score2 < 10 )
		sc2 = "000" + sc2;
	else if ( score2 < 100 )
		sc2 = "00" + sc2;
	else if ( score2 < 1000 )
		sc2 = "0" + sc2;

	if ( hi < 10 )
		hiScore = "000" + hiScore;
	else if ( hi < 100 )
		hiScore = "00" + hiScore;
	else if ( hi < 1000 )
		hiScore = "0" + hiScore;
	
	_scoreOf1.setString( sc1 );
	_scoreOf2.setString( sc2 );
	_scoreOfHi.setString( hiScore );

}

void Score::UpdateLife( int life )
{
	std::string lifeS = std::to_string( life ) + " LIFE";
	_textLife.setString( lifeS );
}

void Score::DrawScore()
{
	_data->window.draw( _textScore1 );
	_data->window.draw( _textScore2 );
	_data->window.draw( _highScore );
	_data->window.draw( _scoreOf1 );
	_data->window.draw( _scoreOf2 );
	_data->window.draw( _scoreOfHi );
	_data->window.draw( _textLife );
}

