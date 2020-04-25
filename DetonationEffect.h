#pragma once

#include <SFML/Graphics.hpp>

#include "ENUMCLASS.h"

class DetonationEffect
{
private:
	sf::Sprite _icon;
	sf::Vector2f _position;
	sf::Clock _timeIsAvailable;

	Type _type;

	bool _isPainted = false;

public:
	DetonationEffect( sf::Vector2f position );
	~DetonationEffect();

	Type getType();
	bool CheckIsAvailable() const;
	sf::Sprite& getSprite();
	bool getIsPainted();
	void setIsPainted( bool isPainted );
};
