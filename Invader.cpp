#include "Invader.h"
#include <string>


Invader::Invader( sf::Vector2f position, int type ) : _position( position )
{
	// Set Image Type.
	_isLive = true;
	_icon.setPosition( _position );

	switch ( type )
	{
	case 0:
		_typeInvader = 1;
		break;
	case 1:
		_typeInvader = 2;
		break;
	case 2:
		_typeInvader = 2;
		break;
	default:
		_typeInvader = 3;
		break;
	}
}

Invader::~Invader()
{

}

sf::Sprite Invader::getSprite()
{
	return _icon;
}

void Invader::setSprite( sf::Texture &texture)
{
	_icon.setTexture( texture );
}

int Invader::getTypeInvader()
{
	return _typeInvader;
}

void Invader::setTypeInvader( int typeInvader )
{
	_typeInvader = typeInvader;
}

void Invader::setPosition( sf::Vector2f position )
{
	_position = position;
	_icon.setPosition( _position );
}

bool Invader::getIsLive()
{
	return _isLive;
}

void Invader::setIsLive( bool isLive )
{
	_isLive = isLive;
}

void Invader::Move( float x, float y )
{
	_position += {x, y};
	_icon.setPosition( _position );
}

sf::Vector2f Invader::getPosition()
{
	return _position;
}

sf::FloatRect Invader::getRectangle()
{
	return
	{
		_icon.getPosition(), {WIDTH, HEIGHT}
	};
}

void Invader::DrawInvader()
{

}
