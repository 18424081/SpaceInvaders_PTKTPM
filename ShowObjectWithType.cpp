#include "ShowObjectWithType.h"

ShowObjectWithType::ShowObjectWithType( GameDataRef data ) : _data( data )
{

}

ShowObjectWithType::~ShowObjectWithType()
{

}

void ShowObjectWithType::renderEntity( sf::Sprite &renderer, Type type )
{
    switch ( type )
    {
    case Type::Rectangle:
        renderer.setTexture( _data->asset.GetTexture( "rectangle" ) );
        break;
    case Type::Lightning:
        renderer.setTexture( _data->asset.GetTexture( "lightning" ) );
        break;
    case Type::Knife:
        renderer.setTexture( _data->asset.GetTexture( "knife" ) );
        break;
    case Type::Explosion:
        renderer.setTexture( _data->asset.GetTexture( "explosion" ) );
        break;
    default:
        break;
    }
       
    _data->window.draw( renderer );
}