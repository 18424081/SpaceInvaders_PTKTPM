#include "AssetManager.h"

#include <SFML/Graphics.hpp>
#include <iostream>

void AssetManager::LoadTexture( std::string name, std::string fileName )
{
	sf::Texture tex;
	if ( tex.loadFromFile( fileName ) )
	{
		this->_texture[name] = tex;
	}
}

sf::Texture& AssetManager::GetTexture( std::string name )
{
	return this->_texture.at( name );
}


void AssetManager::LoadFont( std::string name, std::string fileName )
{
	sf::Font font;

	if ( font.loadFromFile( fileName ) )
	{
		this->_fonts[name] = font;
	}
}

sf::Font& AssetManager::GetFont( std::string name )
{
	return this->_fonts.at( name );
}


void AssetManager::LoadSound( std::string name, std::string fileName )
{
	sf::SoundBuffer soundBuff;

	if ( soundBuff.loadFromFile( fileName ) )
	{
		this->_sounds[name] = soundBuff;
	}
}

sf::SoundBuffer& AssetManager::GetSound( std::string name )
{
	return this->_sounds.at( name );
}
