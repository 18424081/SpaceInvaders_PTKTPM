#include "InvaderManager.h"

#include <string>
#include <cstdlib>
#include <ctime>


InvaderManager::InvaderManager( GameDataRef data ) : _data(data)
{
    _invaderAreLive = 0;
    const int GAP = 10;
    for ( int y = 0; y < 5; y++ ) 
    {
        for ( int x = 0; x < 11; x++ ) 
        {
            float invaderX = x * 43 + ( GAP * x * 3 ) + 43;
            float invaderY = y * 29 + ( GAP * y ) + 29 * 4;
            _invader.emplace_back( sf::Vector2f{ invaderX, invaderY }, y );
            _invaderAreLive++;
        }
    }
    
    _stepGap = sf::seconds( (float)_invaderAreLive / 90.f );
    _currentIcon = 0;

    // Set Sound.
    _soundStep.setBuffer( _data->asset.GetSound( "invaderStep" ) );
    _soundDeath.setBuffer( _data->asset.GetSound( "invaderDeath" ) );
    _soundShoot.setBuffer( _data->asset.GetSound( "invaderShoot" ) );
}

InvaderManager::~InvaderManager()
{

}

void InvaderManager::setVolumn( int vol )
{
    if ( !_isMute )
    {
        _soundDeath.setVolume( vol );
        _soundShoot.setVolume( vol );
        _soundStep.setVolume( vol );
    }

}
int InvaderManager::getVolumn()
{
    return _vol;
}
void InvaderManager::setMute( bool mute )
{
    _isMute = mute;
    _soundDeath.setVolume( 0 );
    _soundShoot.setVolume( 0 );
    _soundStep.setVolume( 0 );
}
bool InvaderManager::getMute()
{
    return _isMute;
}
void InvaderManager::stopSoundAll()
{
    _soundDeath.stop();
    _soundShoot.stop();
    _soundStep.stop();
}

int InvaderManager::getQuantityInvader()
{
    return _invaderAreLive;
}
void InvaderManager::setQuantityInvader( int number )
{
    _invaderAreLive = number;
}

void InvaderManager::StepInvader()
{

    if ( _stepTimer.getElapsedTime() > _stepGap ) {
        _currentIcon++;

        bool moveDown = false;
        float step = _isMovingLeft ? -10.0f : 10.0f;
        if ( _moveDown ) 
        {
            step *= -1;
        }
        _soundStep.play();

        //Move the invaders
        for ( auto& invader : _invader ) 
        {
            if ( !invader.getIsLive() ) continue;
            invader.Move( step, 0.0f );
            if ( _moveDown ) {
                invader.Move( 0, invader.HEIGHT / 2.0f );
            }
            else if ( !moveDown ) 
            {
                moveDown = CheckInvaderPosition( invader );
            }
        }

        if ( _moveDown ) 
            _isMovingLeft = !_isMovingLeft;
        _moveDown = moveDown;
        _stepTimer.restart();
    }
}

bool InvaderManager::CheckInvaderPosition( Invader invader )
{
    if ( invader.getPosition().y > SCREEN_HEIGHT - 150 ) 
    {
        _isGameOver = true;
        std::cout << "Game Over" << std::endl;
    }
    return
        ( invader.getPosition().x < 15 && _isMovingLeft )   // Move Left.
        || ( invader.getPosition().x + invader.WIDTH > SCREEN_WIDTH - 15 && !_isMovingLeft );   // Move Right.
}

bool InvaderManager::CheckIsGameOver()
{
    return _isGameOver;
}


void InvaderManager::UpdateStepInvaderWithTime()
{
    _stepGap = sf::seconds( (float)_invaderAreLive / 90.0f );
}

sf::Vector2f InvaderManager::ChooseItemShoot()
{
    if ( _invaderAreLive == 0 ) return { -1, 0 };
    //Keep looping until an invader is found
    sf::Clock timeT;
    while ( true ) 
    {
        //srand( (int)time( 0 ) ); // làm lag game, có thể do time chạy.
        auto invaderNumber = rand() % 10 + 0;
        for ( int i = 4; i >= 0; i-- ) 
        {
            int index = i * 11 + invaderNumber;
            auto& invader = _invader.at( index );
            if ( invader.getIsLive() )
            {
                _soundShoot.play();
                
                return
                {
                    //transform to below the invader's center
                    invader.getPosition().x + invader.WIDTH / 2,
                    invader.getPosition().y + invader.getSprite().getGlobalBounds().height
                };
            }
        }
    }
}

std::pair<int, std::vector<sf::Vector2f>> InvaderManager::CheckKilledByProjectiles( std::vector<Projectile>& projectiles )
{
    int score = 0;
    if ( _scoreKillInvader.first > 0 )
        _scoreKillInvader.first = 0;
    if ( _scoreKillInvader.second.size() > 0 )
        _scoreKillInvader.second.clear();

    for ( auto& invader : _invader )
    {
        for ( auto& projectile : projectiles )
        {
            if ( !invader.getIsLive() || !projectile.isActive() )
                continue;
            if ( invader.getRectangle().intersects( projectile.getRectangle() ) && projectile.getDirection() == Direction::Up )
            {
                _invaderAreLive--;
                invader.setIsLive( false );
                projectile.destroy();
                _scoreKillInvader.first += invader.getTypeInvader() == 1 ? ( 3 * 100 )
                    : ( invader.getTypeInvader() == 2 ? ( 2 * 100 ) : ( 1 * 100 ) );
                _scoreKillInvader.second.emplace_back( invader.getPosition() );
                _soundDeath.play();
            }
        }
    }
    return _scoreKillInvader;
}


void InvaderManager::DrawArrayInvader()
{
    std::string nameTexture;
    for ( auto& invader : _invader )
    {
        if ( !invader.getIsLive() )
            continue;
        nameTexture = "invader";
        nameTexture += std::to_string( invader.getTypeInvader() );

        if ( _currentIcon % 2 )
            nameTexture += "1";
        else
            nameTexture += "2";

        invader.setSprite( _data->asset.GetTexture( nameTexture ) );
        _data->window.draw( invader.getSprite() );
    }
}


// LAN
std::vector<Invader>& InvaderManager::getInvaderArray()
{
    return _invader;
}

void InvaderManager::setInvaderArray( std::vector<Invader> array )
{
    for ( int i = 0; i < array.size(); i++ )
    {
        if ( _invader.at( i ).getIsLive() != array.at( i ).getIsLive() )
        {
            _invader.at( i ).setIsLive( array.at( i ).getIsLive() );
        }
        if ( _invader.at( i ).getTypeInvader() != array.at( i ).getTypeInvader() )
            _invader.at( i ).setTypeInvader( array.at( i ).getTypeInvader() );
        if ( ( _invader.at( i ).getPosition().x < array.at( i ).getPosition().x ) && _isMovingLeft )
        {
            _invader.at( i ).setPosition( array.at( i ).getPosition() );
            continue;
        }
        if ( ( _invader.at( i ).getPosition().x > array.at( i ).getPosition().x ) && !_isMovingLeft )
        {
            _invader.at( i ).setPosition( array.at( i ).getPosition() );
            continue;
        }
        if ( _invader.at( i ).getPosition().y != array.at( i ).getPosition().y )
        {
            _invader.at( i ).setPosition( array.at( i ).getPosition() );
            continue;
        }
       
        /*_invader.at( i ).setIsLive( array.at( i ).getIsLive() );
        _invader.at( i ).setPosition( array.at( i ).getPosition() );
        _invader.at( i ).setTypeInvader( array.at( i ).getTypeInvader() );*/
    }
}


