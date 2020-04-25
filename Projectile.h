#pragma once


#include <SFML/Graphics.hpp>
#include <vector>

#include "DEFINITIONS.h"
#include "ENUMCLASS.h"
#include "Game.h"
#include "Player.h"

class Projectile
{
private:
    GameDataRef _data;
    sf::Vector2f _position;
    Type _type;
    Direction _direction;
    bool _isActive = true;
    int _id;
    sf::Sprite _icon;
    sf::Texture _temp;

public:
    constexpr static float HEIGHT = 7; // 24
    constexpr static float WIDTH = 3;  // 12

    Projectile( GameDataRef data );
    Projectile( const sf::Vector2f& position, Type type, Direction direction );
    ~Projectile();
    void update( float dt );
    void destroy();

    const sf::Vector2f& getPosition() const;
    Type getType() const;
    bool isActive() const;
    Direction getDirection() const;
    int getID() const;
    sf::Sprite& getSprite();
    sf::FloatRect getRectangle();
    int CheckKillPlayer( Player &player );

    void DrawProjectile( Type type );
};
