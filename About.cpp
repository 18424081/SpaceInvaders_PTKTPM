#include "About.h"
#include "MainMenuState.h"

About::About( GameDataRef data ) : _data( data )
{

}

About::~About()
{

}

void About::Init()
{
	this->_data->asset.LoadTexture( "About", ABOUT );
	this->_data->asset.LoadTexture( "Home Button", HOME_BUTTON );
	
	this->_homeButton.setTexture( this->_data->asset.GetTexture( "Home Button" ) );
	this->_content.setTexture( this->_data->asset.GetTexture( "About" ) );

	this->_content.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_content.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 ) - ( this->_content.getGlobalBounds().height / 2 ) );
	this->_homeButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_homeButton.getGlobalBounds().width / 2 ), ( 700 ) );
}

void About::HandleInput()
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
			this->_data->machine.AddState( StateRef( new MainMenuState( _data ) ), true );
		}
	}
}

void About::Update( float dt )
{
	
}

void About::Draw( float dt )
{
	this->_data->window.clear();

	this->_data->window.draw( this->_content );
	this->_data->window.draw( this->_homeButton );

	this->_data->window.display();
}