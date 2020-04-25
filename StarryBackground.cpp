#include "StarryBackground.h"
#include "DEFINITIONS.h"

StarryBackground::StarryBackground()
{
    for ( int i = 0; i < 500; i++ ) 
    {
        sf::Vertex star;
        RandomStartLocation( star );
        star.position.y -= SCREEN_HEIGHT;
        _stars.push_back( star );
    }
}

void StarryBackground::update( float dt )
{
    for ( auto& star : _stars ) {
        star.position.y -= 250 * dt;
        if ( star.position.y <= 0 ) {
            RandomStartLocation( star );
        }
    }
}

void StarryBackground::draw( sf::RenderTarget& renderer )
{
    renderer.draw( _stars.data(), _stars.size(), sf::Points );
}

void StarryBackground::RandomStartLocation( sf::Vertex& star )
{
    star.position = { _rng.getFloatInRange( 0, (float)SCREEN_WIDTH ),
        _rng.getFloatInRange( (float)SCREEN_HEIGHT, (float)SCREEN_HEIGHT * 2.0f ) };
}
