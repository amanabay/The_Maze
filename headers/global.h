#ifndef GLOBAL_H
#define GLOBAL_H

#include "structs.h"
#include "macros.h"
#include "maze.h"

/* render window */
extern SDL_Window *window;

/* window renderer */
extern SDL_Renderer *renderer;

/* texture */
extern SDL_Texture *texture;

/* buffer for textures */
extern uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

/* array of textures */
extern uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];

/* X and Y start position */
extern Vec_2d pos;

/* initial direction vector */
extern Vec_2d dir;

/* camera plane */
extern Vec_2d plane;

/* time of current frame */
extern double time;

#endif /* GLOBAL_H */
