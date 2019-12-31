#include "Actor.h"



Actor::Actor()
{
	mTexture = nullptr;
	width = 0;
	height = 0;
	actorPosition = SDL_Point{0,0};
}


Actor::~Actor()
{
	free();
}

bool Actor::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	free();

	SDL_Texture* tempTexture = nullptr;

	SDL_Surface* tempSurface = IMG_Load(path.c_str());

	if (tempSurface == nullptr)
	{
		std::cout << "could not load .png file. SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

		setWidth(tempSurface->w);
		setHeight(tempSurface->h);

		tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		if (tempTexture != nullptr)
		{
			setActorTexture(tempTexture);
		}
		SDL_FreeSurface(tempSurface);
	}
	return getActorTexture() != nullptr;
}

void Actor::free()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		width = 0;
		height = 0;
	}
}

void Actor::render(SDL_Renderer* renderer)
{
	int isoTileX = GameUtil::x2DToIso(actorPosition.x, actorPosition.y);
	int isoTileY = GameUtil::y2DToIso(actorPosition.x, actorPosition.y);

	SDL_Rect renderQuad = { isoTileX, isoTileY, width, height };
	SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
}

void Actor::setPosition(int x, int y)
{
	actorPosition.x = x;
	actorPosition.y = y;
}

SDL_Point Actor::getPosition()
{
	return actorPosition;
}

int Actor::getWidth()
{
	return width;
}

int Actor::getHeight()
{
	return height;
}

SDL_Texture* Actor::getActorTexture()
{
	return mTexture;
}

void Actor::setWidth(int w)
{
	width = w;
}

void Actor::setHeight(int h)
{
	height = h;
}

void Actor::setActorTexture(SDL_Texture* tex)
{
	mTexture = tex;
}