#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "DEFINITIONS.h"
#include "ENUMCLASS.h"

class ShowObjectWithType
{
private:
    GameDataRef _data;

public:
    ShowObjectWithType( GameDataRef data );
    ~ShowObjectWithType();

    void renderEntity( sf::Sprite &renderer, Type type );

};
