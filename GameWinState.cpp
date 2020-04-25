#include "GameWinState.h"

#include <sstream>
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include "GameState.h"

#include <iostream>

GameWinState::GameWinState( GameDataRef data, int score ) : _data( data ), _score( score )
{
	_highSc = new HighScore( _data );
	_highSc->setScore( _score );
}

GameWinState::~GameWinState()
{
	delete _highSc;
}

void GameWinState::Init()
{
	/*this->_data->asset.LoadTexture( "Pause Background", PAUSE_BACKGROUND_FILEPATH );
	_background.setTexture( this->_data->asset.GetTexture( "Pause Background" ) );*/
	_highSc->Init();

	this->_data->asset.LoadTexture( "Retry Button", RETRY_BUTTON );
	_resumeButton.setTexture( this->_data->asset.GetTexture( "Retry Button" ) );

	this->_data->asset.LoadTexture( "Home Button", HOME_BUTTON );
	_homeButton.setTexture( this->_data->asset.GetTexture( "Home Button" ) );

	this->_data->asset.LoadTexture( "Submit Button", SUBMIT_BUTTON );
	_submit.setTexture( this->_data->asset.GetTexture( "Submit Button" ) );

	this->_data->asset.LoadTexture( "Winner", GAME_WIN );
	_title.setTexture( this->_data->asset.GetTexture( "Winner" ) );

	this->_title.setPosition( (SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), 0 );

	this->_resumeButton.setPosition( 75, 600 );

	this->_homeButton.setPosition( 375, 600 );

	this->_submit.setPosition( 675, 600 );

}

void GameWinState::HandleInput()
{
	sf::Event event;

	while ( this->_data->window.pollEvent( event ) )
	{
		if ( sf::Event::Closed == event.type )
		{
			this->_data->window.close();
		}
		if ( sf::Event::TextEntered == event.type )
		{
			_nameSubmit += event.text.unicode;
			_highSc->UpdateNameToSubmit( _nameSubmit );
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_resumeButton, sf::Mouse::Left, this->_data->window ) )
		{
			std::cout << "Retry The Game" << std::endl;
			this->_data->machine.AddState( StateRef( new GameState( _data ) ), true );
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_homeButton, sf::Mouse::Left, this->_data->window ) )
		{
			std::cout << "Go Main Menu From HomeButton" << std::endl;
			this->_data->machine.RemoveState();
			this->_data->machine.AddState( StateRef( new MainMenuState( _data ) ), true );
		}

		if ( this->_data->input.IsSpriteClicked(
			this->_submit, sf::Mouse::Left, this->_data->window ) )
		{
			// ghi xuong file diem hien tai.
			std::pair<std::string, std::string> submit = _highSc->getSubmit();
			if ( submit.first.size() > 0 )
			{
				std::ofstream outFile( SCORE_FILE, std::ios::app );
				outFile << submit.first << "," << submit.second << ";";
				outFile.close();
			}
			this->_data->machine.RemoveState();
			this->_data->machine.AddState( StateRef( new MainMenuState( _data ) ), true );
		}
	}
}

void GameWinState::Update( float dt )
{

}

void GameWinState::Draw( float dt )
{
	this->_data->window.clear();

	this->_data->window.draw( this->_resumeButton );
	this->_data->window.draw( this->_homeButton );
	this->_data->window.draw( this->_submit );
	this->_data->window.draw( this->_title );
	_highSc->DrawScore();

	this->_data->window.display();
}