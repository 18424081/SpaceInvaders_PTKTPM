#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "DEFINITIONS.h"
#include "Game.h"


class Player 
{
private:
    GameDataRef _data;

    sf::Sprite _icon;
    sf::Vector2f _position;
    sf::Clock _deathTime;

    bool _isLive = true;
    int _hasLive = 3;
    int _score = 0;
    bool _allowShoot = true;

    sf::Sound _soundDeath;
    sf::Sound _soundShoot;
    bool _isMute;
    int _vol;

    // LAN
    int _id = -1;
    std::string _name = "vinh_handsome";

public:
    const float WIDTH = 47;
    const float HEIGHT = 29;

    Player( GameDataRef data );
    ~Player();

    void Init();

    void input();
    void Update( float dt );
    void DrawPlayer();

    void setVolumn( int vol );
    int getVolumn();
    void setMute( bool mute );
    bool getMute();
    void playSoundDeath();
    void playSoundShoot();
    void stopSoundAll();

    sf::Vector2f getGunPosition();
    sf::Vector2f getPosition();
    int getLives();
    bool getIsLive();
    void setIsLive( bool isLive );
    int getHasLive();
    void setHasLive( int hasLive );
    void setScore( int score );
    int getScore();
    void setAllowShoot( bool isAllow );
    bool getAllowShoot();
    sf::FloatRect getRectangle();
    void Restart();

    // LAN
    int getID();
    void setID( int id );
    std::string getName();

};
