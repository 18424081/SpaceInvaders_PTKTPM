#pragma once

#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////////
//		InputManager CLASS
//		event Mouse Button and get position mouse.
////////////////////////////////////////////////////////////////

class InputManager
{
private:

public:
	InputManager() {}
	~InputManager() {}

	bool IsSpriteClicked( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window );

	sf::Vector2i GetMousePosition( sf::RenderWindow& window );
};