#include "maze.h"

/**
 * main - renders maze
 * @argc: number of arguments
 * @argv: pointer to array of arguments
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];
	Vec_2d pos;
	Vec_2d dir;
	Vec_2d plane;
	double time;

	int *maze; /* 2D array defining maze map */
	char *map_name;
	bool textured;

	/* initial values for global variables */
	pos.x = 1;
	pos.y = 12;
	dir.x = 1;
	dir.y = -0.66;
	plane.x = 0;
	plane.y = 0.66;
	time = 0;

	map_name = "\0";
	textured = true;
	if (argc == 3)
	{
		if (strcmp(argv[2], "flat") == 0)
			textured = false;
		map_name = argv[1];
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "flat") == 0)
		{
			map_name = "maps/map_0";
			textured = false;
		}
		else
			map_name = argv[1];
	}
	else if (argc == 1)
		map_name = "maps/map_0";

	/* start SDL and create window and renderer */
	if (!init_SDL())
		return (1);

	/* parse maze file */
	maze = NULL;
	maze = parse_map(map_name, maze);
	if (maze == NULL)
		return (1);

	if (textured)
		load_textures();

	while (!quit())
	{
		if (!textured)
			render_flat();

		/* draw walls, textured floor, and textured ceiling */
		raycast(maze, textured);

		/* handles user input */
		input(maze);
	}

	close_SDL();
	free(maze);
	return (0);
}
