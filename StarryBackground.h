#pragma once

#include "Random.h"
#include "SFML/Graphics.hpp"

class StarryBackground
{
public:
    StarryBackground();

    void update( float dt );

    void draw( sf::RenderTarget& renderer );

private:
    void RandomStartLocation( sf::Vertex& v );

    std::vector<sf::Vertex> _stars;

    Random<> _rng;
};
