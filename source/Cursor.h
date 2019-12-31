#pragma once
#include "Actor.h"
class Cursor :
	public Actor
{
public:
	const int CURSOR_WIDTH = 12;
	const int CURSOR_HEIGHT = 14;

	void handleEvent(SDL_Event* e);

	virtual void render(SDL_Renderer* renderer)override;

	Cursor();
	~Cursor();
};

