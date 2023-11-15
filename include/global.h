#ifndef GLOBAL_H
#define GLOBAL_H

extern SDL_Window *window;

extern SDL_Renderer *renderer;

extern SDL_Texture *texture;

extern uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

extern uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];

extern Vec_2d pos;

extern Vec_2d dir;

extern Vec_2d plane;

extern double time;

#endif /* GLOBAL_H */
