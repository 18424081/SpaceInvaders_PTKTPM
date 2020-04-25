#include "MainMenuState.h"
#include "GameState.h"
#include "GameStateLan.h"

MainMenuState::MainMenuState( GameDataRef data ) : _data( data )
{

}

MainMenuState::~MainMenuState() {}

void MainMenuState::Init()
{
	this->_data->asset.LoadTexture( "PlayButton", START_BUTTON );
	this->_data->asset.LoadTexture( "GameTitle", MAIN_MENU_TITLE );
	this->_data->asset.LoadTexture( "ExitButton", EXIT_BUTTON );
	this->_data->asset.LoadTexture( "HighScoreButton", HIGHSCORE_BUTTON );

	this->_title.setTexture( this->_data->asset.GetTexture( "GameTitle" ) );
	this->_playButton.setTexture( this->_data->asset.GetTexture( "PlayButton" ) );
	this->_exitButton.setTexture( this->_data->asset.GetTexture( "ExitButton" ) );
	this->_highScore.setTexture( this->_data->asset.GetTexture( "HighScoreButton" ) );

	this->_title.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_title.getGlobalBounds().width / 2 ),
		this->_title.getGlobalBounds().height * 0.1 );

	this->_playButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_playButton.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 - 150 ) - ( this->_playButton.getGlobalBounds().height / 2 ) );
	this->_highScore.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_playButton.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 + 0) - ( this->_playButton.getGlobalBounds().height / 2 ) );
	this->_exitButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_playButton.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 + 150) - ( this->_playButton.getGlobalBounds().height / 2 ) );
	
}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while ( this->_data->window.pollEvent( event ) )
	{
		if ( sf::Event::Closed == event.type )
		{
			this->_data->window.close();
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_playButton, sf::Mouse::Left, this->_data->window ) )
		{
			std::cout << "Go to Game Screen" << std::endl;
			this->_data->machine.AddState( StateRef( new GameState( _data ) ), true );
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_exitButton, sf::Mouse::Left, this->_data->window ) )
		{
			// Exit game.
			std::cout << "Exit Game" << std::endl;
			this->_data->machine.RemoveState();
			this->_data->window.close();

			// Gameplay on LAN.
			//this->_data->machine.AddState( StateRef( new GameStateLan( _data ) ), true );
		}
		if ( this->_data->input.IsSpriteClicked(
			this->_highScore, sf::Mouse::Left, this->_data->window ) )
		{
			std::cout << "Go to HighScore Screen" << std::endl;
			this->_data->machine.AddState( StateRef( new HighScoreState( _data ) ), true );
		}
	}
}
void MainMenuState::Update( float dt )
{
	_background.update( 0.01 );
}

void MainMenuState::Draw( float dt )
{
	this->_data->window.clear();

	this->_background.draw( this->_data->window );
	this->_data->window.draw( this->_title );
	this->_data->window.draw( this->_playButton );
	this->_data->window.draw( this->_exitButton );
	this->_data->window.draw( this->_highScore );

	this->_data->window.display();
}
