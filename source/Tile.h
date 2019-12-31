#pragma once
#include "Actor.h"

class Tile :
	public Actor
{
public:
	Tile();
	~Tile();

	virtual void render(SDL_Renderer* renderer)override;
};

