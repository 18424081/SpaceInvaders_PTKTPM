#include "Player.h"

Player::Player(GameDataRef data) : _data( data )
{
    // Set Image.
	_icon.setTexture( _data->asset.GetTexture( "player1" ) );
	_icon.setPosition( ( SCREEN_WIDTH / 2 ) - ( _icon.getGlobalBounds().width / 2 ), SCREEN_HEIGHT - 30 );

    // Set Sound.
    _soundDeath.setBuffer( _data->asset.GetSound( "playerDeath" ) );
    _soundShoot.setBuffer( _data->asset.GetSound( "playerShoot" ) );
    _isMute = false;
    _vol = 100;

	_isLive = true;
    _score = 0;
    _deathTime.restart();
}

Player::~Player()
{

}

void Player::Init()
{

}

// LAN
int Player::getID()
{
    return _id;
}
void Player::setID( int id )
{
    _id = id;
}
std::string Player::getName()
{
    return _name;
}

void Player::setVolumn( int vol )
{
    if ( !_isMute )
    {
        _soundDeath.setVolume( vol );
        _soundShoot.setVolume( vol );
    }

}
int Player::getVolumn()
{
    return _vol;
}
void Player::setMute( bool mute )
{
    _isMute = mute;
    _soundDeath.setVolume( 0 );
    _soundShoot.setVolume( 0 );
}
bool Player::getMute()
{
    return _isMute;
}

void Player::playSoundDeath()
{
    _soundDeath.play();
}
void Player::playSoundShoot()
{
    _soundShoot.play();
}
void Player::stopSoundAll()
{
    _soundDeath.stop();
    _soundShoot.stop();
}

sf::FloatRect Player::getRectangle()
{
    return
    {
        _icon.getPosition(), {WIDTH, HEIGHT}
    };
}

sf::Vector2f Player::getGunPosition()
{
    return
    {
        _icon.getPosition().x + _icon.getGlobalBounds().width / 2,
        _icon.getPosition().y
    };
}

sf::Vector2f Player::getPosition()
{
    return _icon.getPosition();
}

void Player::setScore( int score )
{
    _score = score;
}
int Player::getScore()
{
    return _score;
}

void Player::setAllowShoot( bool isAllow )
{
    _allowShoot = isAllow;
}
bool Player::getAllowShoot()
{
    return _allowShoot;
}

void Player::setIsLive( bool isLive )
{
    _isLive = isLive;
}

bool Player::getIsLive()
{
    return _isLive;
}

int Player::getHasLive()
{
    return _hasLive;
}

void Player::setHasLive( int hasLive )
{
    _hasLive = hasLive;
}

void Player::Restart()
{
    //_velocity *= 0.0f;
    //_icon.setTextureRect( { 0, 0, 11, 8 } );
    
    if ( _deathTime.getElapsedTime().asSeconds() >= 2.5f ) {
        _isLive = true;
        _hasLive--;
        _icon.setPosition( ( SCREEN_WIDTH / 2 ) - ( _icon.getGlobalBounds().width / 2 ), SCREEN_HEIGHT - 30 );
        _position = _icon.getPosition();
        _deathTime.restart();
    }
}

void Player::input()
{
    using Key = sf::Keyboard::Key;
    auto keyDown = []( sf::Keyboard::Key k ) {
        return sf::Keyboard::isKeyPressed( k );
    };

    float speed = 100;
    if ( keyDown( Key::A ) ) {
        _position.x -= speed;
    }
    else if ( keyDown( Key::D ) ) {
        _position.x += speed;
    }
    else if ( keyDown( Key::Add ) ) {
        _vol++;
        setVolumn( _vol );
    }
    else if ( keyDown( Key::Subtract ) ) {
        _vol--;
        setVolumn( _vol );
    }
    else if ( keyDown( Key::M ) ) {
        _vol = 0;
        setVolumn( _vol );
    }
}


void Player::Update( float dt )
{
    if ( _isLive ) 
    {
        float width = _icon.getGlobalBounds().width;
        _icon.move( _position.x * dt, 0 );
        _position *= 0.7f; //0.95
        if ( _icon.getPosition().x <= 0 ) {
            _position.x = 1.0f;
            _icon.setPosition( 1.0f, SCREEN_HEIGHT - 30 );
        }
        else if ( _icon.getPosition().x + width >= SCREEN_WIDTH ) {
            _position.x = -1.0f;
            _icon.setPosition( SCREEN_WIDTH - 1.0f - width, SCREEN_HEIGHT - 30 );
        }
    }
}

void Player::DrawPlayer()
{
    if ( _isLive )
    {
        _data->window.draw( _icon );
    }
}
