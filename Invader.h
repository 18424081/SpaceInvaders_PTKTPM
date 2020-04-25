#pragma once


#include <SFML/Graphics.hpp>
#include <vector>
#include "Windows.h"

#include "Game.h"
#include "DEFINITIONS.h"

class Invader
{
private:
	GameDataRef _data;

	sf::Texture _icon_Tex;
	sf::Sprite _icon;

	int _typeInvader;
	int _typeIcon;
	sf::Vector2f _position;
	bool _isLive;

public:
	Invader( sf::Vector2f position, int type );
	~Invader();

	sf::Sprite getSprite();
	void setSprite( sf::Texture &texture );
	void setPosition( sf::Vector2f position );
	int getTypeInvader();
	void setTypeInvader( int typeInvader );
	bool getIsLive();
	void setIsLive( bool isLive );
	void Move( float x, float y );
	sf::Vector2f getPosition();
	sf::FloatRect getRectangle();

	void DrawInvader();

	constexpr static float WIDTH = 43;
	constexpr static float HEIGHT = 29;
};
