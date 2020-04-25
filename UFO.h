#pragma once


#include <SFML/Graphics.hpp>

#include "Game.h"
#include "DEFINITIONS.h"

class UFO
{
private:
	GameDataRef _data;

	sf::Texture _texture_0;
	sf::Texture _texture_1;
	sf::Texture _texture_2;
	sf::Sprite _icon;
	sf::Vector2f _position;
	int _addHasLive = 1;
	bool _shootGift = false;
	bool _isLive = true;
	int _textNumber;

	sf::Clock _timeDelay;
	sf::Clock _timeDelayRestartUFO;
	sf::Clock _timeDelaySoundMove;

	sf::Sound _soundDeath;
	sf::Sound _soundMove;
	bool _isMute;

public:
	UFO( GameDataRef data );
	~UFO();

	sf::Sprite getSprite();
	void setSprite( sf::Texture& texture );
	sf::Vector2f getPosition();
	sf::FloatRect getRectangle();
	bool getIsLive();
	void setIsLive( bool isLive );
	void Move( float x, float y );
	int getTextNumber();
	void setTextNumber( int number );
	void setPosition( sf::Vector2f vec );

	void setVolumn( int vol );
	void setMute( bool mute );
	bool getMute();
	void stopSoundAll();

	void Restart();
	void Update( float dt );
	void DrawUFO();

	constexpr static float WIDTH = 88;
	constexpr static float HEIGHT = 39;
};
