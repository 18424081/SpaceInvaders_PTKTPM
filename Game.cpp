#include "Game.h"
#include "SplashState.h"

Game::Game( int width, int height, std::string title )
{
	//sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	this->_data->window.create( sf::VideoMode( width, height ), title.c_str(), sf::Style::Close | sf::Style::Titlebar );
	this->_data->machine.AddState( StateRef( new SplashState( this->_data ) ) );

	this->Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	// Loop Game;
	while ( this->_data->window.isOpen() )
	{
		this->_data->machine.ProcessStateChanges();
		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if ( frameTime > 0.25f )
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while ( accumulator >= this->dt )
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update( this->dt );

			accumulator -= this->dt;
		}

		interpolation = accumulator / this->dt;
		this->_data->machine.GetActiveState()->Draw( interpolation );
	}
}