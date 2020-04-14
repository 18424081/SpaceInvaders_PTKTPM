#pragma once


////////////////////////////////////////////////////////////////
//		State Class
//		Abstract class has Init, Handle control, Update game,
//		Draw is show screen window, Pause game and Resume game.
////////////////////////////////////////////////////////////////

class State
{
public:
	virtual void Init() = 0;

	virtual void HandleInput() = 0;
	virtual void Update( float dt ) = 0;
	virtual void Draw( float dt ) = 0;

	virtual void Pause() {}
	virtual void Resume() {}
};