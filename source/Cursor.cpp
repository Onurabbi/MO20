#include "Cursor.h"



Cursor::Cursor()
{
}


Cursor::~Cursor()
{
}

void Cursor::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		this->setPosition(x, y);
	}
}

void Cursor::render(SDL_Renderer* renderer)
{
	SDL_Rect renderQuad = { getPosition().x, getPosition().y, getWidth(), getHeight() };
	SDL_RenderCopy(renderer, getActorTexture(), nullptr, &renderQuad);
}