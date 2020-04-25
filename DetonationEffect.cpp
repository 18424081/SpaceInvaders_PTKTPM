#include "DetonationEffect.h"

DetonationEffect::DetonationEffect( sf::Vector2f position )
{
	_position = position;
	_icon.setPosition( _position );
	_isPainted = true;
	_type = Type::Explosion;
}
DetonationEffect::~DetonationEffect()
{

}

bool DetonationEffect::CheckIsAvailable() const
{
	return _timeIsAvailable.getElapsedTime().asSeconds() >= 0.2f;
}

sf::Sprite& DetonationEffect::getSprite()
{
	return _icon;
}

bool DetonationEffect::getIsPainted()
{
	return _isPainted;
}
void DetonationEffect::setIsPainted( bool isPainted )
{
	_isPainted = isPainted;
}

Type DetonationEffect::getType()
{
	return _type;
}

