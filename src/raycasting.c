#include "../include/maze.h"
#include "../include/global.h"

/**
 * raycast - casts rays and renders walls, floor, and ceiling
 * @maze: 2D array defining maze map
 * @textured: True if user enabled textures, otherwise False
 * Return: void
 */
void raycast(int *maze, bool textured)
{
	double camera_x;
	Vec_2d ray_pos;
	Vec_2d ray_dir;
	Vec_2d pos_to_next;
	Vec_2d dist_to_next;
	double dist_to_wall;

	SDL_Point map;
	SDL_Point step;

	int hit;
	int side;

	int x;

	/* cast ray x for every column w */
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		camera_x = 2 * x / (double)(SCREEN_WIDTH) - 1;
		ray_pos.x = pos.x;
		ray_pos.y = pos.y;
		ray_dir.x = dir.x + plane.x * camera_x;
		ray_dir.y = dir.y + plane.y * camera_x;

		/* grid position on maze */
		map.x = (int)(ray_pos.x);
		map.y = (int)(ray_pos.y);

		/* measure distance to next X or Y intersection */
		dist_to_next.x = sqrt(1 + (pow(ray_dir.y, 2)) / pow(ray_dir.x, 2));
		dist_to_next.y = sqrt(1 + (pow(ray_dir.x, 2)) / pow(ray_dir.y, 2));

		/* calculate step and distance from pos to first X or Y */
		if (ray_dir.x < 0)
		{
			step.x = -1;
			pos_to_next.x = (ray_pos.x - map.x) * dist_to_next.x;
		}
		else
		{
			step.x = 1;
			pos_to_next.x = (map.x + 1.0 - ray_pos.x) * dist_to_next.x;
		}

		if (ray_dir.y < 0)
		{
			step.y = -1;
			pos_to_next.y = (ray_pos.y - map.y) * dist_to_next.y;
		}
		else
		{
			step.y = 1;
			pos_to_next.y = (map.y + 1.0 - ray_pos.y) * dist_to_next.y;
		}

		/* move to next maze square in X or Y dir until wall is hit */
		hit = 0;
		while (hit == 0)
		{
			if (pos_to_next.x < pos_to_next.y)
			{
				pos_to_next.x += dist_to_next.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				pos_to_next.y += dist_to_next.y;
				map.y += step.y;
				side = 1;
			}

			/* check if ray hit a wall */
			if (*((int *)maze + map.x * MAP_WIDTH + map.y) > 0)
				hit = 1;
		}

		/* calculate distance projected in camera direction */
		if (side == 0)
			dist_to_wall = (map.x - ray_pos.x + (1 - step.x) / 2) / ray_dir.x;
		else
			dist_to_wall = (map.y - ray_pos.y + (1 - step.y) / 2) / ray_dir.y;

		/* draw walls to buffer */
		walls(maze, map, ray_pos, ray_dir, dist_to_wall, x, side, textured);
	}

	/* draw updated buffer with walls, floor, and ceiling to renderer */
	update_renderer(textured);
}
