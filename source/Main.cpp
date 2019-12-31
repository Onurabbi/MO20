#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Actor.h"
#include "Tile.h"
#include "Cursor.h"
#include "GameUtil.h"
#include "Character.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
};

int xIsoTo2D(int x, int y);
int yIsoTo2D(int x, int y);

int x2DToIso(int x, int y);
int y2DToIso(int x, int y);

bool init();

bool loadTiles(std::vector<std::vector<Tile*>> &tiles);
void placeTiles(std::vector<std::vector<Tile*>> &tiles);


void close();

SDL_Window* mainWindow = nullptr;
SDL_Renderer* renderer = nullptr;

std::vector<std::vector<Tile*>> tileVec{};

Cursor cursor;
Cursor* cursorPtr = &cursor;
Character character;
Character* charPtr = &character;

int main(int argc, char* argv[])
{
	if (!init())
	{
		std::cout << "Unable to initialize!" << std::endl;
	}
	else
	{
		if (!loadTiles(tileVec))
		{
			std::cout << "Could not load tiles" << std::endl;
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			cursorPtr->loadFromFile("assets/textures/cursor_1.png", renderer);
			charPtr->loadFromFile("assets/textures/hunter.png", renderer);
			placeTiles(tileVec);

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					cursorPtr->handleEvent(&e);
					charPtr->handleEvent(&e);
				}

				charPtr->update();

				SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);

				SDL_RenderClear(renderer);

				for (int i = 0; i < tileVec.size(); i++)
					for (int j = 0; j < tileVec.at(0).size(); j++)
					{
						tileVec.at(i).at(j)->render(renderer);
					}
				charPtr->render(renderer);
				cursorPtr->render(renderer);
				SDL_RenderPresent(renderer);
			}
			
		}

	}
	close();

	return 0;
}

bool init()
{	//Initialize SDL systems, create window and renderer.
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize SDL! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		mainWindow = SDL_CreateWindow("MO20", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (mainWindow == nullptr)
		{
			std::cout << "Failed to create SDL_Window SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr)
			{
				std::cout << "Failed to create SDL_Renderer SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
				SDL_ShowCursor(SDL_DISABLE);

			}
		}
	}
	return success;
}

bool loadTiles(std::vector<std::vector<Tile*>> &tiles)
{
	bool success = true;
	tiles.resize(12);

	for (int i=0; i<MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			Tile* tempTile = new Tile;

			if (worldMap[i][j] == 0)
			{
				tempTile->loadFromFile("assets/textures/grass_tile.png", renderer);
			}
			else
			{
				tempTile->loadFromFile("assets/textures/dirt_tile.png", renderer);
			}
			if (tempTile == nullptr)
			{
				std::cout << "Can not load tiles." << std::endl;
				success = false;
			}
			else
			{
				tiles.at(i).push_back(tempTile);
			}
		}
	return success;
}


void placeTiles(std::vector<std::vector<Tile*>> &tiles)
{
	for (int i = 0; i < tiles.size(); i++)
		for (int j = 0; j < tiles.at(0).size(); j++)
		{
			tiles.at(i).at(j)->setPosition(500+32*j, 32*i);
		}
}




void close()
{
	for (int i = 0; i < tileVec.size(); i++)
		for (int j = 0; j < tileVec.at(0).size(); j++)
		{
			SDL_DestroyTexture(tileVec.at(i).at(j)->getActorTexture());
		}

	for (int i = 0; i < tileVec.size(); i++)
		for (int j = 0; j < tileVec.at(0).size(); j++)
		{
			delete tileVec.at(i).at(j);
		}
	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainWindow);

	mainWindow = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}