#include "Enemy.h"


Enemy::Enemy( int id, sf::Vector2f position, std::string name ) : m_health( 100 ), m_id( id ), m_name( "default" )
{
	if ( !pTexture.loadFromFile( "Resources/texture/player_2.png" ) )
		std::cout << "Error loading player.png" << std::endl;
	this->setTexture( pTexture );
	this->setPosition( position );
	this->setName( name );
	std::cout << "idenemy " << m_id << std::endl;
}


Enemy::~Enemy()
{
}

