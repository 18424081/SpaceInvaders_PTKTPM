#include <sstream>
#include "GameStateLan.h"
#include "Player.h"

#include <iostream>

GameStateLan::GameStateLan( GameDataRef data ) : _data( data )
{

}

GameStateLan::~GameStateLan()
{
	delete  _score, _includePlayerNInvader;
}

void GameStateLan::Init()
{
	_data->asset.LoadTexture( "player1", PLAYER_1 );
	_data->asset.LoadTexture( "player2", PLAYER_2 );
	_data->asset.LoadTexture( "invader11", INVADER_1_1 );
	_data->asset.LoadTexture( "invader12", INVADER_1_2 );
	_data->asset.LoadTexture( "invader21", INVADER_2_1 );
	_data->asset.LoadTexture( "invader22", INVADER_2_2 );
	_data->asset.LoadTexture( "invader31", INVADER_3_1 );
	_data->asset.LoadTexture( "invader32", INVADER_3_2 );
	_data->asset.LoadTexture( "shield", SHIELD_1 );
	_data->asset.LoadTexture( "ufoRed0", UFO_RED_0 );
	_data->asset.LoadTexture( "ufoRed1", UFO_RED_1 );
	_data->asset.LoadTexture( "ufoRed2", UFO_RED_2 );
	_data->asset.LoadTexture( "rectangle", RECTANGLE );
	_data->asset.LoadTexture( "knife", KNIFE );
	_data->asset.LoadTexture( "lightning", LIGHTNING );
	_data->asset.LoadTexture( "explosion", EXPLOSION_1 );

	_data->asset.LoadFont( "arcade", FONT_ARCADE );

	_data->asset.LoadSound( "invaderStep", SOUND_INVADER_STEP_1 );
	_data->asset.LoadSound( "invaderDeath", SOUND_INVADER_DEATH );
	_data->asset.LoadSound( "invaderShoot", SOUND_INVADER_SHOOT );
	_data->asset.LoadSound( "playerDeath", SOUND_PLAYER_DEATH );
	_data->asset.LoadSound( "playerShoot", SOUND_PLAYER_SHOOT );
	_data->asset.LoadSound( "ufoDeath", SOUND_UFO_DEATH );
	_data->asset.LoadSound( "ufoMove", SOUND_UFO_MOVE );

	_score = new Score( _data );
	_includePlayerNInvader = new IncludePlayerNInvader( _data, true );
}

void GameStateLan::HandleInput()
{
	sf::Event event;
	while ( this->_data->window.pollEvent( event ) )
	{
		if ( sf::Event::Closed == event.type )
		{
			this->_data->window.close();
		}

		if ( sf::Event::KeyPressed == event.type )
		{
			if ( event.key.code == sf::Keyboard::P )
			{
				std::cout << "Pause The Game" << std::endl;
				this->_data->machine.AddState( StateRef( new PauseState( _data ) ), false );
			}
		}
	}

	if ( _includePlayerNInvader->checkWinGame() )
		this->_data->machine.AddState( StateRef( new PauseState( _data ) ), false );
	else
	{
		_includePlayerNInvader->HandleInput();
	}
}

void GameStateLan::Update( float dt )
{
	_includePlayerNInvader->Update( dt );
	_score->UpdateScore( _includePlayerNInvader->getScoreWorld(), 0 );
	_score->UpdateLife( _includePlayerNInvader->getLifePlayer() );
}

void GameStateLan::Draw( float dt )
{
	this->_data->window.clear();

	_score->DrawScore();
	_includePlayerNInvader->Draw();

	this->_data->window.display();
}

