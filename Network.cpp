#include "Network.h"


Network::Network( sf::IpAddress& ip, unsigned short& port, GameDataRef data ) : _connected( false ), _data( data )
{
	if ( connection.connect( ip, port, sf::seconds( 5 ) ) != sf::Socket::Done )
	{
		_checkConnect = false;
		std::cout << "Error connecting to server" << std::endl;
	}
	else
	{
		connection.setBlocking( false );
		_checkConnect = true;
		std::cout << "Connected" << std::endl;
	}
}


void Network::disconnect( Player* p )
{
	sf::Packet temp;
	temp << 1;
	temp << p->getID();

	if ( connection.send( temp ) != sf::Socket::Done )
	{
		std::cout << "Error sending to server" << std::endl;
	}
	else
	{
		std::cout << "Disconnected" << std::endl;
	}
}

bool Network::getCheckConnected()
{
	return _checkConnect;
}

void Network::send( Player* p )
{
	sf::Packet temp;
	temp << 3;
	temp << p->getID();
	temp << p->getPosition().x;
	temp << p->getPosition().y;

	if ( connection.send( temp ) != sf::Socket::Done )
	{
		std::cout << "Error sending data to server" << std::endl;
	}


}

// Send Projectile.
void Network::SendProjectile( std::vector<Projectile> projectile, Player* player )
{
	sf::Packet pk;
	pk << 4;
	pk << player->getID();
	pk << projectile.size();
	for ( std::vector<Projectile>::iterator it = projectile.begin(); it != projectile.end(); ++it )
	{
		pk << it->getPosition().x;
		pk << it->getPosition().y;
		pk << (int)it->getType();
		pk << (int)it->getDirection();
	}
		
	if ( connection.send( pk ) != sf::Socket::Done )
	{
		std::cout << "Error sending projectile to server" << std::endl;
	}
}

// Send UFO.
void Network::SendUFO( UFO* ufo, Player* player )
{
	sf::Packet pk;
	pk << 5;
	pk << player->getID();
	pk << ufo->getTextNumber();
	pk << ufo->getPosition().x;
	pk << ufo->getPosition().y;
	pk << ufo->getIsLive();

	if ( connection.send( pk ) != sf::Socket::Done )
	{
		std::cout << "Error sending projectile to server" << std::endl;
	}
}

// Send InvaderManager.
void Network::SendInvaderManager( InvaderManager* invaderArray, Player* player )
{
	sf::Packet pk;
	pk << 6;
	pk << player->getID();
	pk << invaderArray->getQuantityInvader();
	for ( auto& invader : invaderArray->getInvaderArray() )
	{
		pk << invader.getIsLive();
		pk << invader.getPosition().x;
		pk << invader.getPosition().y;
		pk << invader.getTypeInvader();
	}
	if ( connection.send( pk ) != sf::Socket::Done )
	{
		std::cout << "Error sending projectile to server" << std::endl;
	}
}


void Network::getPlayerList( Player* p )
{
	sf::Packet temp;
	temp << 7;
	temp << p->getID();

	if ( connection.send( temp ) != sf::Socket::Done )
	{
		std::cout << "Error sending getPlayerList to server" << std::endl;
	}
}

void Network::receive(PlayerRed *playerRed , Player* p )
{
	sf::Packet receivePacket;
	int type, id;
	if ( connection.receive( receivePacket ) == sf::Socket::Done )
	{
		
		receivePacket >> type;
		receivePacket >> id;
		if ( type == 0 ) // you connected to server, get your ID
		{
			if ( p->getID() == -1 )
			{
				p->setID( id );
				std::cout << "Connected to server with ID: " << p->getID() << std::endl;
				sf::sleep( sf::milliseconds( 50 ) );
				this->getPlayerList( p );
			}
			_connected = true;
		}

		else if ( type == 3 ) // get move direction of playerRed
		{

			if ( playerRed->getID() == id )
			{
				sf::Vector2f dir;
				receivePacket >> dir.x;
				receivePacket >> dir.y;

				playerRed->setPosition( dir );
			}
		}
		else if ( type == 4 ) // Received Projectile.
		{
			if ( playerRed->getID() == id )
			{
				if ( playerRed->getArrayProjectile().size() > 0 )
					playerRed->getArrayProjectile().clear();

				std::vector<Projectile> array;
				
				int size;
				sf::Vector2f vec;
				int typeP;
				int direct;
				receivePacket >> size;
				for ( int i = 0; i < size; i++ )
				{
					receivePacket >> vec.x;
					receivePacket >> vec.y;
					receivePacket >> typeP;
					receivePacket >> direct;
					array.emplace_back( vec, (Type)typeP, (Direction)direct );
				}
				playerRed->setArrayProjectile( array );
			}
		}
		else if ( type == 5 ) // Receive UFO.
		{
			if ( playerRed->getID() == id )
			{
				int textNumberUFO;
				sf::Vector2f vec;
				bool isLive;
				receivePacket >> textNumberUFO;
				receivePacket >> vec.x;
				receivePacket >> vec.y;
				receivePacket >> isLive;

				playerRed->getUFORed()->setPosition( vec );
				playerRed->getUFORed()->setTextNumber( textNumberUFO );
				playerRed->getUFORed()->setIsLive( isLive );
			}
		}

		else if ( type == 6 ) // Receive InvaderManager.
		{
			if ( playerRed->getID() == id )
			{
				bool isLive;
				sf::Vector2f vec;
				int typeInvader;
				int invaderAreLive;
				receivePacket >> invaderAreLive;
				playerRed->getInvaderManager()->setQuantityInvader( invaderAreLive );
				for ( int i = 0; i < 55; i++ )
				{
					receivePacket >> isLive;
					receivePacket >> vec.x;
					receivePacket >> vec.y;
					receivePacket >> typeInvader;
					playerRed->getInvaderManager()->getInvaderArray().at( i ).setIsLive( isLive );
					playerRed->getInvaderManager()->getInvaderArray().at( i ).setPosition( vec );
					playerRed->getInvaderManager()->getInvaderArray().at( i ).setTypeInvader( typeInvader );
				}
			}
		}

		else if ( type == 7 ) //Create new players
		{
			int playerNumber;
			std::vector<std::string> playersName;
			std::vector<int> playersId;

			receivePacket >> playerNumber;
			std::cout << "Num of players on server: " << playerNumber << std::endl;

			for ( int i = 0; i < playerNumber; ++i )
			{
				std::string tempName;
				int tempId;
				receivePacket >> tempId;
				receivePacket >> tempName;
				playersName.push_back( tempName );
				playersId.push_back( tempId );

			}


			for ( unsigned int i = 0; i < playersId.size(); ++i )
			{
				bool haveThatEnemy = false;
				if ( playerRed->getID() == playersId[i] )
				{
					haveThatEnemy = true;
				}
				if ( playersId[i] != p->getID() && !haveThatEnemy )
				{
					playerRed->setID( playersId[i] );
					_textMessage = "New player: " + playersName[i];
				}
			}
			playersName.clear();
			playersId.clear();
		}
	}
}

