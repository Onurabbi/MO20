#pragma once
#include "Actor.h"
#include "GameUtil.h"
#include <cmath>


class Character :
	public Actor
{
public:
	const int MOVE_VEL = 5;

	bool isMoving;

	Character();
	~Character();

	void move(int x, int y);

	void handleEvent(SDL_Event* e);
	void update();

	int getVelX();
	int getVelY();

	void setVelX(int vel);
	void setVely(int vel);

	void setDest(SDL_Point dest);

	virtual void render(SDL_Renderer* renderer)override;

private:
	int velX;
	int velY;
	SDL_Point dest;

};

