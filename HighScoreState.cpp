#include "HighScoreState.h"
#include "MainMenuState.h"

HighScoreState::HighScoreState( GameDataRef data ) : _data( data )
{
	_highScore = new HighScore( _data );
}

HighScoreState::~HighScoreState()
{
	delete _highScore;
}

void HighScoreState::Init()
{
	_highScore->ShowOnlyHighScore();
	this->_data->asset.LoadTexture( "Home Button", HOME_BUTTON );

	this->_homeButton.setTexture( this->_data->asset.GetTexture( "Home Button" ) );

	this->_homeButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_homeButton.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 + 350 ) - ( this->_homeButton.getGlobalBounds().height / 2 ) );
}

void HighScoreState::HandleInput()
{
	sf::Event event;

	while ( this->_data->window.pollEvent( event ) )
	{
		if ( sf::Event::Closed == event.type )
		{
			this->_data->window.close();
		}
		if ( this->_data->input.IsSpriteClicked(
			this->_homeButton, sf::Mouse::Left, this->_data->window ) )
		{
			std::cout << "Go Main Menu From HomeButton" << std::endl;
			this->_data->machine.RemoveState();
			this->_data->machine.AddState( StateRef( new MainMenuState( _data ) ), true );
		}
	}
}

void HighScoreState::Update( float dt )
{
	this->_homeButton.setPosition( 500, 600 );
}

void HighScoreState::Draw( float dt )
{
	this->_data->window.clear();

	this->_data->window.draw( this->_homeButton );
	_highScore->DrawOnlyHighScore();

	this->_data->window.display();
}