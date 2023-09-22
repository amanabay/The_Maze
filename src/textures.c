#include "maze.h"

/**
 * load_textures - loads textures from file and puts
 *		pixel information in buffer
 * Return: void
 */
void load_textures(void)
{
	SDL_Surface * tex_src[TEX_COUNT];
	uint8_t *pixel;
	int i, j, k;

	tex_src[0] = IMG_Load("textures/brick_1.png");
	tex_src[1] = IMG_Load("textures/brick_2.png");
	tex_src[2] = IMG_Load("textures/gate.png");
	tex_src[3] = IMG_Load("textures/brick_1.png");
	tex_src[4] = IMG_Load("textures/sky.png");
	tex_src[5] = IMG_Load("textures/floor.png");

	/* get colors from texture pixels and put in array */
	for (i = 0; i < TEX_COUNT; i++)
	{
		for (j = 0; j < TEX_HEIGHT; j++)
		{
			for (k = 0; k < TEX_WIDTH; k++)
			{
				pixel = (uint8_t *)tex_src[i]->pixels
					+ k * tex_src[i]->pitch + j *
					tex_src[i]->format->BytesPerPixel;

				tiles[i][j][k] = pixel[0] | pixel[1] << 8
					| pixel[2] << 16;
			}
		}
	}

	for (i = 0; i < TEX_COUNT; i++)
	{
		SDL_FreeSurface(tex_src[i]);
		tex_src[i] = NULL;
	}
}
