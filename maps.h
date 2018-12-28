// I think I'm done here...
#pragma once
#include "images.h"

int mapx = 0;
int mapy = 0;

#define WORLD_HEIGHT    8
#define WORLD_WIDTH    14
#define GRASS    0
#define LEFT_SIDE_FIELD    1
#define T_FIELD    2
#define RIGHT_SIDE_OF_FIELD    3
#define B_FIELD    4
#define TL_CORNER    5
#define TR_CORNER    6
#define BL_CORNER    7
#define BR_CORNER    8

int world [WORLD_HEIGHT] [WORLD_WIDTH] =
{
	{ TL_CORNER, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, T_FIELD, TR_CORNER },
	{ LEFT_SIDE_FIELD, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, RIGHT_SIDE_OF_FIELD },
	{ LEFT_SIDE_FIELD, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, RIGHT_SIDE_OF_FIELD },
	{ LEFT_SIDE_FIELD, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, RIGHT_SIDE_OF_FIELD },
	{ LEFT_SIDE_FIELD, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, RIGHT_SIDE_OF_FIELD },
	{ LEFT_SIDE_FIELD, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, RIGHT_SIDE_OF_FIELD },
	{ LEFT_SIDE_FIELD, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, GRASS, RIGHT_SIDE_OF_FIELD },
	{ BL_CORNER, B_FIELD,  B_FIELD, B_FIELD, B_FIELD, B_FIELD,  B_FIELD, B_FIELD, B_FIELD, B_FIELD,  B_FIELD, B_FIELD, B_FIELD, BR_CORNER }
};

#define TILE_SIZE      16
void drawworld()
{
	const int tileswide = ((WIDTH / TILE_SIZE) + 1);
	const int tilestall = ((HEIGHT / TILE_SIZE) + 1);

	for(int y = 0; y < tilestall; y++)
	{
		for(int x = 0; x < tileswide; x++)
		{
			const int tilex = (x - (mapx / TILE_SIZE));
			const int tiley = (y - (mapy / TILE_SIZE));

			if((tilex >= 0) && (tiley >= 0) && (tilex < WORLD_WIDTH) && (tiley < WORLD_HEIGHT))
			{
				arduboy.drawBitmap(x * TILE_SIZE + mapx % TILE_SIZE, y * TILE_SIZE + mapy % TILE_SIZE, tiles[world[tiley][tilex]], TILE_SIZE, TILE_SIZE, WHITE);
			}   
		}
	}
}
