#include "GameOverState.h"

#include <sstream>
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "GameState.h"

#include <iostream>

GameOverState::GameOverState( GameDataRef data ) : _data( data )
{

}

void GameOverState::Init()
{
	this->_data->asset.LoadTexture( "Retry Button", RETRY_BUTTON );
	_retryButton.setTexture( this->_data->asset.GetTexture( "Retry Button" ) );

	this->_data->asset.LoadTexture( "Game Over", GAME_OVER );
	_title.setTexture( this->_data->asset.GetTexture( "Game Over" ) );

	this->_data->asset.LoadTexture( "Home Button", HOME_BUTTON );
	_homeButton.setTexture( this->_data->asset.GetTexture( "Home Button" ) );

	this->_retryButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_retryButton.getLocalBounds().width / 2 ),
		( SCREEN_HEIGHT / 3 ) - ( this->_retryButton.getLocalBounds().height / 2 ) );

	this->_title.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_title.getLocalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 ) - 50 );

	this->_homeButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_homeButton.getLocalBounds().width / 2 ),
		( SCREEN_HEIGHT / 3 * 2 ) - ( this->_homeButton.getLocalBounds().height / 2 ) );

}

void GameOverState::HandleInput()
{
	sf::Event event;

	while ( this->_data->window.pollEvent( event ) )
	{
		if ( sf::Event::Closed == event.type )
		{
			this->_data->window.close();
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_retryButton, sf::Mouse::Left, this->_data->window ) )
		{
			std::cout << "Retry The Game" << std::endl;
			this->_data->machine.RemoveState();
			this->_data->machine.AddState( StateRef( new GameState( _data ) ), true );
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

void GameOverState::Update( float dt )
{
	this->_background.update( 0.01 );
}

void GameOverState::Draw( float dt )
{
	this->_data->window.clear();

	this->_background.draw( this->_data->window );
	this->_data->window.draw( this->_homeButton );
	this->_data->window.draw( this->_retryButton );
	this->_data->window.draw( this->_title );

	this->_data->window.display();
}