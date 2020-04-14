#include "MainMenuState.h"

MainMenuState::MainMenuState( GameDataRef data ) : _data( data )
{

}

MainMenuState::~MainMenuState() {}

void MainMenuState::Init()
{
	this->_data->asset.LoadTexture( "PlayButton", MAIN_MENU_PLAY_BUTTON );
	this->_data->asset.LoadTexture( "GameTitle", MAIN_MENU_TITLE );
	this->_data->asset.LoadTexture( "ExitButton", MAIN_MENU_EXIT_BUTTON );

	this->_title.setTexture( this->_data->asset.GetTexture( "GameTitle" ) );
	this->_playButton.setTexture( this->_data->asset.GetTexture( "PlayButton" ) );
	this->_exitButton.setTexture( this->_data->asset.GetTexture( "ExitButton" ) );

	this->_title.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_title.getGlobalBounds().width / 2 ),
		this->_title.getGlobalBounds().height * 0.1 );
	this->_playButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_playButton.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 - 50 ) - ( this->_playButton.getGlobalBounds().height / 2 ) );
	this->_exitButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_playButton.getGlobalBounds().width / 2 ),
		( SCREEN_HEIGHT / 2 + 200) - ( this->_playButton.getGlobalBounds().height / 2 ) );
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
			//this->_data->machine.AddState( StateRef( new GameState( _data ) ), true );
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_exitButton, sf::Mouse::Left, this->_data->window ) )
		{
			// Exit game.
			std::cout << "Exit Game" << std::endl;
			//this->_data->window.close();
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

	this->_data->window.display();
}
