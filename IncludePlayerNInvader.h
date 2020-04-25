#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>

#include "Player.h"
#include "PlayerRed.h"
#include "InvaderManager.h"
#include "Projectile.h"
#include "ShowObjectWithType.h"
#include "UFO.h"
#include "DetonationEffect.h"
#include "ENUMCLASS.h"

// LAN
#include "Enemy.h"
#include "Network.h"

class IncludePlayerNInvader
{
private:
	GameDataRef _data;

	Player* _player;
	InvaderManager* _invaderManager;
	ShowObjectWithType* _show;
	UFO* _ufo;
	std::vector<Projectile> _projectile;
	std::vector<DetonationEffect> _detonationEffect;
	sf::Clock _playerShootClock;
	sf::Clock _invaderShootClock;
	sf::Clock _paintExplosion;
	int _scoreWorld = 0;
	bool _winGame = false;
	bool _overGame = false;
	std::pair<int, std::vector<sf::Vector2f>> _scoreNInvaderDeath;

	int _vol;

	// Suport LAN
	//std::unique_ptr<PlayerRed> _playerRed;
	PlayerRed* _playerRed;
	bool _lan = false;
	sf::Clock _clockCheckConnect;
	sf::TcpSocket socket;
	unsigned short port;
	sf::IpAddress ipAdress;
	sf::Clock _clock;
	std::vector<sf::Sprite> remotePlayers;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::unique_ptr<Network> network;
	sf::Vector2f lastDirSent;
	bool movingDiagonal;
	sf::Time _positionTimer;
	STARTUPINFO         startInfo = { 0 };
	PROCESS_INFORMATION processInfo = { 0 };
	bool callServer;

public:
	IncludePlayerNInvader(GameDataRef data, bool isLan);
	~IncludePlayerNInvader();

	int getLifePlayer();

	void playerFire();
	void invaderFire();
	void UpdateProjectileNCheckKilledPlayer( float dt );
	int CheckCollision( float dt );
	int getScoreWorld();
	bool checkWinGame();
	bool checkOverGame();

	void HandleInput();
	void Update( float dt );
	void Draw();

	// LAN
	void setIsLan( bool isLan ) { _lan = isLan; }
};

