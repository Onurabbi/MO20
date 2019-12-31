#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "GameUtil.h"


class Actor
{
public:

	Actor();
	~Actor();

	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	void free();

	virtual void render(SDL_Renderer* renderer);

	void setPosition(int x, int y);

	SDL_Point getPosition();

	SDL_Texture* getActorTexture();

	void setActorTexture(SDL_Texture* tex);

	int getWidth();
	int getHeight();

	void setWidth(int w);
	void setHeight(int h);

private:

	SDL_Texture* mTexture;
	SDL_Point actorPosition;
	int width, height;

};

