#include "SplashState.h"
#include "MainMenuState.h"

SplashState::SplashState( GameDataRef data ) : _data( data )
{

}

SplashState::~SplashState()
{

}

void SplashState::Init()
{
	this->_data->asset.LoadTexture( "GameTitle", MAIN_MENU_TITLE );
	this->_title.setTexture( this->_data->asset.GetTexture( "GameTitle" ) );
	this->_title.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_title.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 ) - ( this->_title.getGlobalBounds().height / 2 ) );
}

void SplashState::HandleInput()
{
	sf::Event event;

	while ( this->_data->window.pollEvent( event ) )
	{
		if ( sf::Event::Closed == event.type )
		{
			this->_data->window.close();
		}
	}
}

void SplashState::Update( float dt )
{
	this->_background.update( 0.01 );
	if ( this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME )
	{
		std::cout << "Go to Main Menu" << std::endl;
		// Switch to the Main Menu.
		std::cout << "Switch to Main Menu" << std::endl;
		this->_data->machine.AddState( StateRef( new MainMenuState( _data ) ), true );
	}
}

void SplashState::Draw( float dt )
{
	this->_data->window.clear();

	this->_background.draw( this->_data->window );
	this->_data->window.draw( this->_title );

	this->_data->window.display();
}