#include "PauseState.h"

#include <sstream>
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "GameState.h"

#include <iostream>

PauseState::PauseState( GameDataRef data ) : _data( data )
{

}

void PauseState::Init()
{
	/*this->_data->asset.LoadTexture( "Pause Background", PAUSE_BACKGROUND_FILEPATH );
	_background.setTexture( this->_data->asset.GetTexture( "Pause Background" ) );*/

	this->_data->asset.LoadTexture( "Resume Button", RESUME_BUTTON );
	_resumeButton.setTexture( this->_data->asset.GetTexture( "Resume Button" ) );

	this->_data->asset.LoadTexture( "Home Button", HOME_BUTTON );
	_homeButton.setTexture( this->_data->asset.GetTexture( "Home Button" ) );

	this->_resumeButton.setPosition( ( this->_data->window.getSize().x / 2 ) - ( this->_resumeButton.getLocalBounds().width / 2 ),
		( this->_data->window.getSize().y / 3 ) - ( this->_resumeButton.getLocalBounds().height / 2 ) );

	this->_homeButton.setPosition( ( this->_data->window.getSize().x / 2 ) - ( this->_homeButton.getLocalBounds().width / 2 ),
		( this->_data->window.getSize().y / 3 * 2 ) - ( this->_homeButton.getLocalBounds().height / 2 ) );

}

void PauseState::HandleInput()
{
	sf::Event event;

	while ( this->_data->window.pollEvent( event ) )
	{
		if ( sf::Event::Closed == event.type )
		{
			this->_data->window.close();
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_resumeButton, sf::Mouse::Left, this->_data->window ) )
		{
			std::cout << "Resume The Game" << std::endl;
			this->_data->machine.RemoveState();
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

void PauseState::Update( float dt )
{

}

void PauseState::Draw( float dt )
{
	this->_data->window.clear();

	this->_background.draw( this->_data->window );
	this->_data->window.draw( this->_resumeButton );
	this->_data->window.draw( this->_homeButton );

	this->_data->window.display();
}