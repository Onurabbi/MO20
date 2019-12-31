#include "Character.h"



Character::Character()
{
	velX = 0;
	velY = 0;
	setPosition(500, 500);
}


Character::~Character()
{
}

void Character::update()
{
	if (isMoving)
	{
		move(dest.x, dest.y);
	}
}

void Character::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		isMoving = true;
		SDL_Point destination = GameUtil::getTileCoordinates(x, y);

		this->setDest(destination);

		int deltaX = getPosition().x - dest.x;
		int deltaY = getPosition().y - dest.y;

		double theta = atan(double(deltaX) / double(deltaY));

		velX = int(MOVE_VEL * cos(theta));
		velY = int(MOVE_VEL * sin(theta));

	}
}

void Character::move(int x, int y)
{
	if (this->getPosition().x == x && this->getPosition().y == y)
		isMoving = false;
	else
	{
		int tempX = getPosition().x + velX;
		int tempY = getPosition().y + velY;
		setPosition(tempX, tempY);
	}
}

void Character::setDest(SDL_Point destination)
{
	dest = destination;
}

int Character::getVelX()
{
	return velX;
}
int Character::getVelY()
{
	return velY;
}

void Character::setVelX(int vel)
{
	velX = vel;
}
void Character::setVely(int vel)
{
	velY = vel;
}

void Character::render(SDL_Renderer* rend)
{
	Actor::render(rend);
}
