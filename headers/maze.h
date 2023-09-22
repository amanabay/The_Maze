#ifndef MAZE_H
#define MAZE_H

/* header files */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "structs.h" /* struct definitions */
#include "macros.h" /* macros */
#include "global.h"

int *parse_map(char *filename, int *map);
void load_textures();

bool init_SDL(void);
void update_renderer(bool textured);
void close_SDL(void);

void input(int *maze);
bool quit(void);

void raycast(int *maze, bool textured);
void walls(int *maze, SDL_Point map, Vec_2d rayPos, Vec_2d rayDir,
		double distToWall, int x, int side, bool textured);
void render_flat(void);
void render_tex(SDL_Point map, Vec_2d rayDir, double distToWall,
		double wallX, int drawEnd, int x, int side);

#endif /* MAZE_H */
