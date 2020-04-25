#include "PlayerRed.h"

PlayerRed::PlayerRed( GameDataRef data ) : _data( data )
{
    // Set Image.
    _icon.setTexture( _data->asset.GetTexture( "player2" ) );
    _icon.setPosition( ( SCREEN_WIDTH / 2 ) - ( _icon.getGlobalBounds().width / 2 ), SCREEN_HEIGHT - 30 );

    // Set Sound.
    _soundDeath.setBuffer( _data->asset.GetSound( "playerDeath" ) );
    _soundShoot.setBuffer( _data->asset.GetSound( "playerShoot" ) );
    _isMute = false;
    _vol = 100;

    _isLive = true;
    _score = 0;
    _deathTime.restart();

    // LAN
    _ufoRed = new UFO( _data );
    _invaderManagerRed = new InvaderManager( _data );
}

PlayerRed::~PlayerRed()
{
    delete _ufoRed, _invaderManagerRed;
}

void PlayerRed::Init()
{

}

// LAN
int PlayerRed::getID()
{
    return _id;
}
void PlayerRed::setID( int id )
{
    _id = id;
}
std::string PlayerRed::getName()
{
    return _name;
}

void PlayerRed::setVolumn( int vol )
{
    if ( !_isMute )
    {
        _soundDeath.setVolume( vol );
        _soundShoot.setVolume( vol );
    }

}
int PlayerRed::getVolumn()
{
    return _vol;
}
void PlayerRed::setMute( bool mute )
{
    _isMute = mute;
    _soundDeath.setVolume( 0 );
    _soundShoot.setVolume( 0 );
}
bool PlayerRed::getMute()
{
    return _isMute;
}

void PlayerRed::playSoundDeath()
{
    _soundDeath.play();
}
void PlayerRed::playSoundShoot()
{
    _soundShoot.play();
}
void PlayerRed::stopSoundAll()
{
    _soundDeath.stop();
    _soundShoot.stop();
}

sf::FloatRect PlayerRed::getRectangle()
{
    return
    {
        _icon.getPosition(), {WIDTH, HEIGHT}
    };
}

sf::Vector2f PlayerRed::getGunPosition()
{
    return
    {
        _icon.getPosition().x + _icon.getGlobalBounds().width / 2,
        _icon.getPosition().y
    };
}

sf::Vector2f PlayerRed::getPosition()
{
    return _icon.getPosition();
}

void PlayerRed::setPosition( sf::Vector2f position )
{
    _icon.setPosition( position );
}

void PlayerRed::setScore( int score )
{
    _score = score;
}
int PlayerRed::getScore()
{
    return _score;
}

void PlayerRed::setAllowShoot( bool isAllow )
{
    _allowShoot = isAllow;
}
bool PlayerRed::getAllowShoot()
{
    return _allowShoot;
}

void PlayerRed::setIsLive( bool isLive )
{
    _isLive = isLive;
}

bool PlayerRed::getIsLive()
{
    return _isLive;
}

int PlayerRed::getHasLive()
{
    return _hasLive;
}

void PlayerRed::setHasLive( int hasLive )
{
    _hasLive = hasLive;
}

void PlayerRed::Restart()
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

void PlayerRed::input()
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


void PlayerRed::Update( float dt )
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

void PlayerRed::DrawPlayer()
{
    if ( _isLive )
    {
        _data->window.draw( _icon );
    }
}

// LAN
std::vector<Projectile>& PlayerRed::getArrayProjectile()
{
    return _arrayProjecileRed;
}

void PlayerRed::setArrayProjectile( std::vector<Projectile> array )
{
    if ( _arrayProjecileRed.size() > 0 )
    {
        _arrayProjecileRed.insert( _arrayProjecileRed.end(), array.begin(), array.end() );
    }

    if ( _arrayProjecileRed.size() == 0 )
    {
        for ( auto& a : array )
            _arrayProjecileRed.emplace_back( a );
    }
}

void PlayerRed::setUFOPosition( sf::Vector2f vec )
{
    _ufoRed->setPosition( vec );
}
void PlayerRed::setUFOTextNumber( int number )
{
    _ufoRed->setTextNumber( number );
}
UFO* PlayerRed::getUFORed()
{
    return _ufoRed;
}

InvaderManager* PlayerRed::getInvaderManager()
{
    return _invaderManagerRed;
}

void PlayerRed::setArrayInvader( std::vector<Invader> arrayInvader )
{
    _invaderManagerRed->setInvaderArray( arrayInvader );
}



