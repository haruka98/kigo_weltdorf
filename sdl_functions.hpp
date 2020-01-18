#ifndef SDL_FUNCTIONS_HPP
#define SDL_FUNCTIONS_HPP

#include "includeheader.hpp"

int init_sdl(char* window_name);
int close_sdl();

void render();
void clear_render();

SDL_Color nCol(int r, int g, int b);
void render_text(char* text, int x, int y, int size, int center, int f_color);

void render_person(int x, int y);
void render_big_person(int x, int y, int color);
void init_person();
void quit_person();

void render_screen();

void render_statistics(int color[100]);

void render_buttons();
void render_arrow(int x, int y);

#endif
