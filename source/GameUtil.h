#pragma once
#include <SDL.h>

const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 1280;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int MAP_WIDTH = 12;
const int MAP_HEIGHT = 12;

class GameUtil
{
public:

	static int xIsoTo2D(int x, int y);
	static int yIsoTo2D(int x, int y);

	static int x2DToIso(int x, int y);
	static int y2DToIso(int x, int y);

	static SDL_Point getTileCoordinates(int x, int y);

	GameUtil();
	~GameUtil();
};

