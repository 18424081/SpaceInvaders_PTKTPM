#include "IncludePlayerNInvader.h"

#include <cstdlib>
#include <ctime>



IncludePlayerNInvader::IncludePlayerNInvader( GameDataRef data, bool isLan ) :_data( data ), _lan( isLan )
{
	_invaderManager = new InvaderManager( _data );
	_player = new Player( _data );
	_show = new ShowObjectWithType( _data );
	_ufo = new UFO( _data );

	// LAN connect.
	if ( _lan )
	{
		port = 45000;
		ipAdress = ipAdress.getLocalAddress();
		std::cout << ipAdress << std::endl;
		network = std::make_unique<Network>( ipAdress, port, _data );
		socket.setBlocking( false );

		if ( network->getCheckConnected() )
		{
			// Create new Player.
			_playerRed = new PlayerRed( _data ); // other syntax //_playerRed = std::make_unique<PlayerRed>( _data );
			std::cout << "Da tao player Red" << std::endl;
		}
	}
}

IncludePlayerNInvader::~IncludePlayerNInvader()
{
	// LAN
	if ( _lan )
	{
		network->disconnect( std::move( _player ) );
		delete _playerRed;
	}
	
	_player->stopSoundAll();
	_invaderManager->stopSoundAll();
	_ufo->stopSoundAll();

	delete _player, _invaderManager, _show, _ufo;
}

int IncludePlayerNInvader::getLifePlayer()
{
	return _player->getHasLive();
}

bool IncludePlayerNInvader::checkWinGame()
{
	return _winGame;
}
bool IncludePlayerNInvader::checkOverGame()
{
	return _overGame;
}

int IncludePlayerNInvader::getScoreWorld()
{
	return _scoreWorld;
}

void IncludePlayerNInvader::HandleInput()
{
	// Xử lý cho player.
	if ( _data->window.hasFocus() )
	{
		if ( _player->getIsLive() )
		{
			_player->input();
			_vol = _player->getVolumn();
			playerFire();
			
			// LAN
			if ( _lan && network->getCheckConnected() )
			{
				network->SendProjectile( _projectile, _player );
			}

			_invaderManager->setVolumn( _vol );
			_ufo->setVolumn( _vol );
		}
		else if ( _player->getHasLive() > 0 )
		{
			// restart player.
			_player->Restart();
		}
		else if ( _player->getHasLive() <= 0 )
		{
			_overGame = true;
			std::cout << "game over" << std::endl;
		}
	}

	// LAN
	if ( _lan && network->getCheckConnected() )
	{
		network->receive( _playerRed, _player );
		if ( _playerRed->getID() != -1 )
		{
			_playerRed->setPosition( _playerRed->getPosition() );
		}
	}
}

void IncludePlayerNInvader::Update( float dt )
{
	int score = 0;
	// If number of invader < 0 is game win.
	if ( _invaderManager->getQuantityInvader() > 0 )
	{
		if ( _scoreNInvaderDeath.second.size() > 0 )
			_scoreNInvaderDeath.second.clear();
		if ( _scoreNInvaderDeath.first > 0 )
			_scoreNInvaderDeath.first = 0;
		if ( _detonationEffect.size() > 0 )
			_detonationEffect.clear();
		
		_player->Update( dt );
		if ( _player->getIsLive() )
		{
			
			// LAN Send Player.
			if ( _lan && network->getCheckConnected() )
			{
				network->send(_player);
			}

			_invaderManager->StepInvader();
			invaderFire();
			CheckCollision( dt );

			
			// Create array effect fire.
			if ( _scoreNInvaderDeath.second.size() > 0 )
			{
				score += _scoreNInvaderDeath.first;
				for ( auto& scoreNInvaderDeath : _scoreNInvaderDeath.second )
				{
					_detonationEffect.emplace_back( scoreNInvaderDeath );
				}
			}

			_invaderManager->UpdateStepInvaderWithTime();
			// Check Over And Win.
			if ( _invaderManager->CheckIsGameOver() )
			{
				_overGame = true;
			}
			// LAN InvaderManager.
			if ( _lan && network->getCheckConnected() )
			{
				network->SendInvaderManager( _invaderManager, _player );
			}
			_ufo->Update( dt );
			// LAN UFO
			if ( _lan && network->getCheckConnected() )
			{
				network->SendUFO( _ufo, _player );
			}
			
			
			// LAN Update.
			if ( _lan && network->getCheckConnected() )
			{
				network->receive( _playerRed, _player );

				_ufo->setPosition( _playerRed->getUFORed()->getPosition() );
				_ufo->setTextNumber( _playerRed->getUFORed()->getTextNumber() );
				_ufo->setIsLive( _playerRed->getUFORed()->getIsLive() );
			}
			// LAN Update.
			if ( _lan && network->getCheckConnected() )
			{
				network->receive( _playerRed, _player );
				_invaderManager->setInvaderArray( _playerRed->getInvaderManager()->getInvaderArray() );
				if ( _invaderManager->getQuantityInvader() > _playerRed->getInvaderManager()->getQuantityInvader() )
				{
					_invaderManager->setQuantityInvader( _playerRed->getInvaderManager()->getQuantityInvader() );
				}
			}

		}
		for ( auto itr = _detonationEffect.begin(); itr != _detonationEffect.end();)
		{
			if ( itr->CheckIsAvailable() ) 
				itr = _detonationEffect.erase( itr );
			else 
				itr++;
		}
	}
	else
	{
		if ( _projectile.size() > 0 )
			_projectile.clear();
		if ( _detonationEffect.size() > 0 )
			_detonationEffect.clear();
		std::cout << "Game win" << std::endl;
		_winGame = true;
	}
	_scoreWorld += score;
	
	// LAN
	if ( _lan && network->getCheckConnected() )
	{
		network->receive( _playerRed, _player );
	}
}


// PLAYER SHOOT.
void IncludePlayerNInvader::playerFire()
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && _playerShootClock.getElapsedTime().asSeconds() > 0.5f )
	{
        sf::Vector2f point = _player->getGunPosition();
		point.y -= float( Projectile::HEIGHT ) + 10.f;
		point.x -= float( Projectile::WIDTH ) / 2.0f;
		_projectile.emplace_back( point, Type::Rectangle, Direction::Up );
		_playerShootClock.restart();
		_player->playSoundShoot();
    }
}

// INVADER SHOOT.
void IncludePlayerNInvader::invaderFire()
{
	if ( _invaderShootClock.getElapsedTime().asSeconds() >= 0.4f )
	{
		sf::Vector2f point = _invaderManager->ChooseItemShoot();
		if ( (int)point.x == -1 ) return;
		srand( time( 0 ) );
		auto type = static_cast<Type>( rand() % 2 + 1 );
		_projectile.emplace_back( point, type, Direction::Down );
		_invaderShootClock.restart();
	}
}

int IncludePlayerNInvader::CheckCollision( float dt )
{
	
	// Check kill invader.
	_scoreNInvaderDeath = _invaderManager->CheckKilledByProjectiles( _projectile );

	// Check kill player.
	UpdateProjectileNCheckKilledPlayer( dt );

	// Check kill UFO.
	for ( auto& projectile : _projectile )
	{
		if ( _ufo->getRectangle().intersects( projectile.getRectangle() ) && projectile.getDirection() == Direction::Up )
		{
			_scoreNInvaderDeath.first += 300;
			_scoreNInvaderDeath.second.emplace_back( _ufo->getPosition() );
			_ufo->setIsLive( false );
		}

		// Check projectile kill projectile other.
		for ( auto& projectOther : _projectile ) 
		{
			if ( projectOther.getRectangle().intersects( projectile.getRectangle() ) 
				&& projectOther.getDirection() != projectile.getDirection() ) 
			{
				projectOther.destroy();
				projectile.destroy();
				_scoreNInvaderDeath.second.emplace_back( projectile.getPosition() );
			}
		}
	}

	return _scoreNInvaderDeath.first;
}

void IncludePlayerNInvader::UpdateProjectileNCheckKilledPlayer( float dt )
{
	for ( auto itr = _projectile.begin(); itr != _projectile.end();) {
		auto& projectile = *itr;
		if ( !projectile.isActive() ) {
			itr = _projectile.erase( itr );
		}
		else {
			// Kill Player.
			if ( projectile.CheckKillPlayer( *_player ) )
			{
				_projectile.clear();
				_player->playSoundDeath();
				return;
			}
			// Projectile Update.
			projectile.update( dt );
			itr++;
		}
	}
}



void IncludePlayerNInvader::Draw()
{
	if ( !_lan )
	{
		_invaderManager->DrawArrayInvader();
		_player->DrawPlayer();
		_ufo->DrawUFO();

		for ( auto& projectile : _projectile )
		{
			if ( projectile.isActive() )
				_show->renderEntity( projectile.getSprite(), projectile.getType() );
		}


		for ( auto& detonationEffect : _detonationEffect )
		{
			_show->renderEntity( detonationEffect.getSprite(), detonationEffect.getType() );

		}
	}
	
	// DRAW FOR PLAYER_RED.
	else if ( _lan && network->getCheckConnected() && _playerRed->getID() != -1 )
	{
		if ( !_playerRed->getID() % 2 )
		{
			
			_invaderManager->DrawArrayInvader();
		}
		else
		{
			_invaderManager->DrawArrayInvader();
			//_playerRed->getInvaderManager()->DrawArrayInvader();
			
		}

		_player->DrawPlayer();
		_playerRed->DrawPlayer();
		for ( auto& projectile : _projectile )
		{
			if ( projectile.isActive() )
				_show->renderEntity( projectile.getSprite(), projectile.getType() );
		}
		for ( auto& projectile : _playerRed->getArrayProjectile() )
		{
			_show->renderEntity( projectile.getSprite(), projectile.getType() );
		}
		_playerRed->getUFORed()->DrawUFO();
	}
		

}




// Open SpaceInvader_PTKTPM_Server.exe
//bool callServer = CreateProcess( TEXT( "V://workspace_C_visual//SpaceInvaders_PTKTPM//Server//SpaceInvader_PTKTPM_Server.exe" ),
//	NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startInfo, &processInfo );
//
//////////// disconect
//if ( callServer )
//{
//	::WaitForSingleObject( processInfo.hProcess, INFINITE );
//	CloseHandle( processInfo.hProcess );
//	CloseHandle( processInfo.hThread );
//}
/////////////////////
