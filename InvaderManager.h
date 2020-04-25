#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Invader.h"
#include "Game.h"
#include "DEFINITIONS.h"
#include "Projectile.h"


class InvaderManager
{
private:
	std::vector<Invader> _invader;
	GameDataRef _data;

	sf::Clock _stepTimer;
	sf::Time _stepGap;
	int _currentIcon;
	int _invaderAreLive;
	bool _isMovingLeft = false;
	bool _moveDown = false;
	bool _isGameOver = false;
	std::pair<int, std::vector<sf::Vector2f>> _scoreKillInvader;

	sf::Sound _soundStep;
	sf::Sound _soundDeath;
	sf::Sound _soundShoot;
	bool _isMute;
	int _vol;

public:

	InvaderManager( GameDataRef data );
	~InvaderManager();

	void setVolumn( int vol );
	int getVolumn();
	void setMute( bool mute );
	bool getMute();
	void stopSoundAll();

	bool CheckIsGameOver();
	int getQuantityInvader();
	void setQuantityInvader( int number );
	bool CheckInvaderPosition( Invader invader );
	void StepInvader();
	void UpdateStepInvaderWithTime();
	sf::Vector2f ChooseItemShoot();
	std::pair<int, std::vector<sf::Vector2f>> CheckKilledByProjectiles( std::vector<Projectile>& projectiles );

	void DrawArrayInvader();

	// LAN
	std::vector<Invader>& getInvaderArray();
	void setInvaderArray( std::vector<Invader> array );

};

