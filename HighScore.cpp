#include "HighScore.h"

bool sortbysec( const std::pair<std::string, int>& a,
	const std::pair<std::string, int>& b )
{
	return ( a.second > b.second );
}

HighScore::HighScore( GameDataRef data ) : _data( data )
{
	
}

HighScore::~HighScore()
{

}

void HighScore::Init()
{
	std::vector<std::pair<std::string, int>> nameNScore;
	std::ifstream pathFile( SCORE_FILE );
	std::string line;
	while ( std::getline( pathFile, line, ';' ) )
	{
		std::string name;
		int score;
		name = line.substr( 0, line.find( "," ) );
		std::istringstream( line.substr( line.find( "," ) + 1, line.size() ) ) >> score;
		std::pair<std::string, int> tempPair( name, score );
		nameNScore.emplace_back( tempPair );
	}
	pathFile.close();
	// Sort DESC.
	std::sort( nameNScore.begin(), nameNScore.end(), sortbysec );

	_data->asset.LoadFont( "arcade", FONT_ARCADE );

	_arrayText.clear();
	int i = 0;
	for ( auto& item : nameNScore )
	{
		sf::Text nameText;
		sf::Text scoreText;
		nameText.setString( item.first );
		nameText.setPosition( 400, 150 + i );
		nameText.setFont( _data->asset.GetFont( "arcade" ) );
		nameText.setFillColor( sf::Color::White );
		nameText.setOutlineColor( sf::Color::Black );
		nameText.setCharacterSize( 25 );

		scoreText.setString( std::to_string( item.second ) );
		scoreText.setPosition( 600, 150 + i );
		scoreText.setFont( _data->asset.GetFont( "arcade" ) );
		scoreText.setFillColor( sf::Color::White );
		scoreText.setOutlineColor( sf::Color::Black );
		scoreText.setCharacterSize( 25 );

		_arrayText.emplace_back( nameText );
		_arrayText.emplace_back( scoreText );

		i += 50;
	}
	sf::Text nameText;
	sf::Text scoreText;
	nameText.setString( "YOUR SCORE" );
	nameText.setPosition( 400, 550 );
	nameText.setFont( _data->asset.GetFont( "arcade" ) );
	nameText.setFillColor( sf::Color::White );
	nameText.setOutlineColor( sf::Color::Black );
	nameText.setCharacterSize( 25 );

	scoreText.setString( std::to_string( _score ) );
	scoreText.setPosition( 600, 550 );
	scoreText.setFont( _data->asset.GetFont( "arcade" ) );
	scoreText.setFillColor( sf::Color::White );
	scoreText.setOutlineColor( sf::Color::Black );
	scoreText.setCharacterSize( 25 );
	_arrayText.emplace_back( nameText );
	_arrayText.emplace_back( scoreText );

	UpdateNameToSubmit("");
}

void HighScore::setScore( int score )
{
	_score = score;
}

void HighScore::ShowOnlyHighScore()
{
	std::vector<std::pair<std::string, int>> nameNScore;
	std::ifstream pathFile( SCORE_FILE );
	std::string line;
	while ( std::getline( pathFile, line, ';' ) )
	{
		std::string name;
		int score;
		name = line.substr( 0, line.find( "," ) );
		std::istringstream( line.substr( line.find( "," ) + 1, line.size() ) ) >> score;
		std::pair<std::string, int> tempPair( name, score );
		nameNScore.emplace_back( tempPair );
	}
	pathFile.close();
	// Sort DESC.
	std::sort( nameNScore.begin(), nameNScore.end(), sortbysec );
	_data->asset.LoadFont( "arcade", FONT_ARCADE );

	_arrayText.clear();
	int i = 0;
	for ( auto& item : nameNScore )
	{
		sf::Text nameText;
		sf::Text scoreText;
		nameText.setString( item.first );
		nameText.setPosition( 400, 150 + i );
		nameText.setFont( _data->asset.GetFont( "arcade" ) );
		nameText.setFillColor( sf::Color::White );
		nameText.setOutlineColor( sf::Color::Black );
		nameText.setCharacterSize( 25 );

		scoreText.setString( std::to_string( item.second ) );
		scoreText.setPosition( 600, 150 + i );
		scoreText.setFont( _data->asset.GetFont( "arcade" ) );
		scoreText.setFillColor( sf::Color::White );
		scoreText.setOutlineColor( sf::Color::Black );
		scoreText.setCharacterSize( 25 );

		_arrayText.emplace_back( nameText );
		_arrayText.emplace_back( scoreText );

		i += 50;
	}
}

void HighScore::UpdateNameToSubmit(std::string name )
{
	_nameSubmit = name;
	std::string s = "TYPE YOUR NAME AND PRESS SUBMIT   ";
	_nameTextSm.setString( s + name );
	_nameTextSm.setFont( _data->asset.GetFont( "arcade" ) );
	_nameTextSm.setFillColor( sf::Color::White );
	_nameTextSm.setOutlineColor( sf::Color::Black );
	_nameTextSm.setCharacterSize( 25 );
	_nameTextSm.setLetterSpacing( 2.0f );
	_nameTextSm.setPosition( ( SCREEN_WIDTH / 2 ) - _nameTextSm.getGlobalBounds().width / 2, 450 );
}

std::pair<std::string, std::string> HighScore::getSubmit()
{
	return std::pair<std::string, std::string>( _nameSubmit, std::to_string( _score ) );
}


void HighScore::DrawScore()
{
	int size = _arrayText.size() < 10 ? _arrayText.size() : 5 * 2;
	for ( int i = 0; i < size; i++ )
	{
		this->_data->window.draw( _arrayText[i] );
	}

	this->_data->window.draw( _nameTextSm );
}

void HighScore::DrawOnlyHighScore()
{
	int size = _arrayText.size() < 10 ? _arrayText.size() : 5 * 2;
	for ( int i = 0; i < size; i++ )
	{
		this->_data->window.draw( _arrayText[i] );
	}
}

