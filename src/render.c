#include "maze.h"

/**
 * walls - draws slice of wall to buffer
 * @maze: 2D array defining maze map
 * @map: X/Y coordinates of box of maze currently in
 * @rayPos: X/Y coordinates of ray position
 * @rayDir: direction of X/Y coordinates of ray position
 * @distToWall: distance to wall from camera
 * @x: number of ray casted
 * @side: determines whether wall is N/S or E/W
 * @textured: True if user enabled textures, otherwise False
 * Return: void
 */
void walls(int *maze, SDL_Point map, Vec_2d rayPos, Vec_2d rayDir,
		double distToWall, int x, int side, bool textured)
{
	int draw_start;
	int draw_end;
	int slice_height;
	int tile_index;
	int width;
	int height;
	int y;
	double wallX;
	SDL_Point tex;
	uint32_t color;

	if (!textured)
	{
		SDL_GetWindowSize(window, &width, &height);

		slice_height = (int)(height / distToWall);

		draw_start = -slice_height / 2 + height / 2;
		if (draw_start < 0)
			draw_start = 0;

		draw_end = slice_height / 2 + height / 2;
		if (draw_end >= height)
			draw_end = height - 1;

		if (side == 0)
			SDL_SetRenderDrawColor(renderer, 0xF7, 0xF7, 0xF7, 0xFF);
		else if (side == 1)
			SDL_SetRenderDrawColor(renderer, 0xDE, 0xDE, 0xDE, 0xFF);

		SDL_RenderDrawLine(renderer, x, draw_start, x, draw_end);
	}
	else
	{
		slice_height = (int)(SCREEN_HEIGHT / distToWall);

		draw_start = -slice_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;

		draw_end = slice_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		wallX = 0;
		if (side == 0)
			wallX = rayPos.y + distToWall * rayDir.y;
		else if (side == 1)
			wallX = rayPos.x + distToWall * rayDir.x;

		tile_index = *((int *)maze + map.x * MAP_WIDTH + map.y) - 1;

		wallX -= floor(wallX);

		tex.x = (int)(wallX * (double)TEX_WIDTH);
		if (side == 0 && rayDir.x > 0)
			tex.x = TEX_WIDTH - tex.x - 1;
		if (side == 1 && rayDir.y < 0)
			tex.x = TEX_WIDTH - tex.x - 1;

		for (y = draw_start; y < draw_end; y++)
		{
			tex.y = ((((y << 1) - SCREEN_HEIGHT + slice_height) <<
				(int)log2(TEX_HEIGHT)) / slice_height) >> 1;

			color = tiles[tile_index][tex.x][tex.y];

			if (side == 1)
				color = (color >> 1) & 8355711;

			buffer[y][x] = color;
		}

		render_tex(map, rayDir, distToWall, wallX, draw_end, x, side);
	}
}

/**
 * render_tex - draws floor and ceiling with textures
 * @map: X/Y coordinates of box of maze currently in
 * @rayDir: direction of X/Y coordinates of ray position
 * @distToWall: distance to wall from camera
 * @wallX: X position of where wall was hit by raycaster
 * @draw_end: end position of wall slice that was drawn
 * @x: number of ray casted
 * @side: determines whether wall is N/S or E/W
 * Return: void
 */
void render_tex(SDL_Point map, Vec_2d rayDir, double distToWall,
		double wallX, int draw_end, int x, int side)
{
	Vec_2d floor_wall; /* X/Y position of floor pixel at bottom of wall */
	Vec_2d floor; /* X/Y position of current floor pixel */
	SDL_Point floor_tex; /* X/Y position corresponding to texture */
	double weight; /* used to find position of pixel between player and wall */
	double dist;
	int y;

	if (side == 0 && rayDir.x > 0)
	{
		floor_wall.x = map.x;
		floor_wall.y = map.y + wallX;
	}
	else if (side == 0 && rayDir.x < 0)
	{
		floor_wall.x = map.x + 1.0;
		floor_wall.y = map.y + wallX;
	}
	else if (side == 1 && rayDir.y > 0)
	{
		floor_wall.x = map.x + wallX;
		floor_wall.y = map.y;
	}
	else
	{
		floor_wall.x = map.x + wallX;
		floor_wall.y = map.y + 1.0;
	}

	if (draw_end < 0)
		draw_end = SCREEN_HEIGHT;

	for (y = draw_end + 1; y < SCREEN_HEIGHT; y++)
	{
		dist = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);

		weight = dist / distToWall;

		floor.x = weight * floor_wall.x + (1.0 - weight) * pos.x;
		floor.y = weight * floor_wall.y + (1.0 - weight) * pos.y;

		floor_tex.x = (int)(floor.x * TEX_WIDTH) % TEX_WIDTH;
		floor_tex.y = (int)(floor.y * TEX_HEIGHT) % TEX_HEIGHT;

		buffer[y][x] = tiles[5][floor_tex.y][floor_tex.x];

		buffer[SCREEN_HEIGHT - y][x] = tiles[4][floor_tex.y][floor_tex.x];
	}
}

/**
 * render_flat - draws ceiling and floor for flat maze
 * Return: void
 */
void render_flat(void)
{
	SDL_Rect ceiling; /* rect for top half of window */
	SDL_Rect floor; /* rect for bottom half of window */
	int width; /* current window width */
	int height; /* current window height */

	SDL_GetWindowSize(window, &width, &height);

	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.w = width;
	ceiling.h = height;

	floor.x = 0;
	floor.y = height / 2;
	floor.w = width;
	floor.h = height / 2;

	/* draw ceiling */
	SDL_SetRenderDrawColor(renderer, 0x59, 0x85, 0x94, 0xFF);
	SDL_RenderFillRect(renderer, &ceiling);

	/* draw floor */
	SDL_SetRenderDrawColor(renderer, 0x1E, 0x29, 0x34, 0xFF);
	SDL_RenderFillRect(renderer, &floor);
}
