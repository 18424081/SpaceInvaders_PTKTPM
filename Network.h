#pragma once

#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "Player.h"
#include "PlayerRed.h"
#include "Enemy.h"
#include "Game.h"
#include "Projectile.h"
#include "ENUMCLASS.h"
#include "UFO.h"


class Network
{
public:
	Network( sf::IpAddress& ip, unsigned short& port, GameDataRef data );
	void disconnect( Player* p );

	void send( Player* p );
	void receive( PlayerRed* player, Player* p );
	void getPlayerList( Player* p );

	std::string getMessage() { return _textMessage; }

	bool getCheckConnected();
	void SendProjectile( std::vector<Projectile> projectile, Player* player );
	void SendUFO( UFO* ufo, Player* player );
	void SendInvaderManager( InvaderManager* invaderArray, Player* player );

private:
	GameDataRef _data;
	sf::TcpSocket connection;
	bool _connected;
	bool _checkConnect;

	std::string _textMessage;
	int packetCounter = 0;
	sf::Clock packetClock;
};

