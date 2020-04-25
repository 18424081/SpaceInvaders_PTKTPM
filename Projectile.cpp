#include "Projectile.h"

Projectile::Projectile( GameDataRef data ) : _data( data )
{
    //_temp = ( _data->asset.GetTexture( "rectangle" ) );
}

Projectile::Projectile( const sf::Vector2f& position, Type type, Direction direction ):
     _position( position )
    , _type( type )
    , _direction( direction )
{
    _icon.setPosition( _position );
    _icon.setScale(3.f, 3.f);

    static int ID = 0;
    _id = ID++;
}

Projectile::~Projectile()
{

}

void Projectile::update( float dt )
{
    float speed = 550 * (float)_direction * dt;
    _position.y += speed;
    _icon.setPosition( _icon.getPosition().x, _position.y );
    if ( _position.y <= 0 || _position.y >= SCREEN_HEIGHT ) {
        destroy();
    }
}

//void Projectile::onCollide( Collidable& other )
//{
//    destroy();
//}

void Projectile::destroy()
{
    _isActive = false;
}

const sf::Vector2f& Projectile::getPosition() const
{
    return _position;
}

Type Projectile::getType() const
{
    return _type;
}

bool Projectile::isActive() const
{
    return _isActive;
}

Direction Projectile::getDirection() const
{
    return _direction;
}

int Projectile::getID() const
{
    return _id;
}

sf::Sprite& Projectile::getSprite()
{
    return _icon;
}


sf::FloatRect Projectile::getRectangle()
{
    return
    {
        _icon.getPosition(), {WIDTH, HEIGHT}
    };
}

int Projectile::CheckKillPlayer( Player& player )
{
    if ( player.getIsLive() && _isActive )
    {
        if ( getRectangle().intersects( player.getRectangle() ) )
        {
            std::cout << "Kill player" << std::endl;
            player.setIsLive( false );
            return 1;
        }
    }
		
	return 0;
}

void Projectile::DrawProjectile( Type type )
{
    _icon.setPosition( _position );
    _icon.setTexture( _temp );
    _data->window.draw( _icon );
}
