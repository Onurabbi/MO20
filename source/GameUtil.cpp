#include "GameUtil.h"



GameUtil::GameUtil()
{
}


GameUtil::~GameUtil()
{
}

int GameUtil::xIsoTo2D(int x, int y)
{
	int cartX = (2 * y + x) / 2;
	return cartX;
}

int GameUtil::yIsoTo2D(int x, int y)
{
	int cartY = (2 * y - x) / 2;
	return cartY;
}



int GameUtil::x2DToIso(int x, int y)
{
	int xIso = x - y;
	return xIso;
}

int GameUtil::y2DToIso(int x, int y)
{
	int yIso = (x + y) / 2;
	return yIso;
}

SDL_Point GameUtil::getTileCoordinates(int x, int y)
{
	SDL_Point tempPoint{ 0,0 };

	tempPoint.x = floor(x / TILE_WIDTH);
	tempPoint.y = floor(y / TILE_HEIGHT);

	return tempPoint;
}