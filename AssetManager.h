#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

////////////////////////////////////////////////////////////////
//		ASSETMANAGER CLASS
//		Set and load image under Texture.
//		Set and load font unser Texture.
////////////////////////////////////////////////////////////////

class AssetManager
{
public:
	AssetManager() {}
	~AssetManager() {}

	void LoadTexture( std::string name, std::string fileName );
	sf::Texture& GetTexture( std::string name );

	void LoadFont( std::string name, std::string fileName );
	sf::Font& GetFont( std::string name );

	void LoadSound( std::string name, std::string fileName );
	sf::SoundBuffer& GetSound( std::string name );

private:
	std::map<std::string, sf::Texture> _texture;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::SoundBuffer> _sounds;
};