#include "includeheader.hpp"
#include "sdl_functions.hpp"

extern int screen_width;
extern int screen_height;

int main(int argc, char* argv[]) {
	int quit = 0;
	int can_use_mouse = 1;
	int x = 0;
	int y = 0;
	SDL_Event e;
	if(init_sdl("KiGo Weltdorf") != 0) {
		return -1;
	}
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(SDL_MOUSEBUTTONUP) {
				can_use_mouse = 1;
			}
			if(e.type == SDL_QUIT) {
				quit = 1;
			} else {
				SDL_GetMouseState(&x, &y);
				// mouse input
			}
		}
		clear_render();
		// render screen
		render_screen();
		render();
	}
	close_sdl();
	return 0;
}
