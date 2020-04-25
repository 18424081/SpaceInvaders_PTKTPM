#include "UFO.h"

UFO::UFO( GameDataRef data ) : _data( data )
{
    // Set Image.
    _texture_0 = _data->asset.GetTexture( "ufoRed0" );
    _texture_1 = _data->asset.GetTexture( "ufoRed1" );
    _texture_2 = _data->asset.GetTexture( "ufoRed2" );
    _icon.setPosition( - WIDTH * 5, SCREEN_HEIGHT - 730 );
    _position = _icon.getPosition();

    // Set Sound.
    _soundDeath.setBuffer( _data->asset.GetSound( "ufoDeath" ) );
    _soundMove.setBuffer( _data->asset.GetSound( "ufoMove" ) );
    _isMute = false;
}
UFO::~UFO()
{

}

int UFO::getTextNumber()
{
    return _textNumber;
}
void UFO::setTextNumber( int number )
{
    _textNumber = number;
}

void UFO::setPosition( sf::Vector2f vec )
{
    _position = vec;
    _icon.setPosition( _position );
}

sf::Sprite UFO::getSprite()
{
	return _icon;
}
void UFO::setSprite( sf::Texture& texture )
{
	_icon.setTexture( texture );
}
sf::Vector2f UFO::getPosition()
{
	return _position;
}
sf::FloatRect UFO::getRectangle()
{
	return
	{
		_icon.getPosition(), {WIDTH, HEIGHT}
	};
}

bool UFO::getIsLive()
{
	return _isLive;
}

void UFO::setIsLive( bool isLive )
{
    _isLive = isLive;
}

void UFO::Move( float x, float y )
{
	_position += {x, y};
}

void UFO::Restart()
{
    _icon.setPosition( -WIDTH * 5, SCREEN_HEIGHT - 730 );
    _position = _icon.getPosition();
    _isLive = true;
}

void UFO::setVolumn( int vol )
{
    if ( !_isMute )
    {
        _soundDeath.setVolume( vol );
        _soundMove.setVolume( vol );
    }
    
}
void UFO::setMute( bool mute )
{
    _isMute = mute;
    _soundDeath.setVolume( 0 );
    _soundMove.setVolume( 0 );
}
bool UFO::getMute()
{
    return _isMute;
}
void UFO::stopSoundAll()
{
    _soundDeath.stop();
    _soundMove.stop();
}

void UFO::Update( float dt )
{
    if ( _isLive )
    {
        _icon.move( 200.0f * dt, 0 );
        //_position.x *= 0.7f; //0.95
        if ( _icon.getPosition().x - _icon.getGlobalBounds().width >= SCREEN_WIDTH ) 
        {
            _icon.setPosition( -WIDTH * 5, SCREEN_HEIGHT - 730 );
            _position = _icon.getPosition();
        }
        _position = _icon.getPosition();
        
        /*if (_position.x >= 0 && _position.x < SCREEN_WIDTH && _timeDelaySoundMove.getElapsedTime().asSeconds() > 0.2f )
            _soundMove.play();
        _timeDelaySoundMove.restart();*/
    }
    else
    {
        _soundDeath.play();
        Restart();
    }
}

void UFO::DrawUFO()
{
    if ( _timeDelay.getElapsedTime().asSeconds() > 0.2f)
    {
        _timeDelay.restart();
        switch ( _textNumber )
        {
        case 2:
            _icon.setTexture( _texture_2 );
            _textNumber = 1;
            break;
        case 1:
            _icon.setTexture( _texture_1 );
            _textNumber = 0;
            break;
        case 0:
            _icon.setTexture( _texture_0 );
            _textNumber = 2;
            break;
        default:
            break;
        }
        
    }
    if (_isLive )
        _data->window.draw( _icon );
}
