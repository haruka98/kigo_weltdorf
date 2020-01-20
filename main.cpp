#include "includeheader.hpp"
#include "sdl_functions.hpp"

extern int screen_width;
extern int screen_height;

int main(int argc, char* argv[]) {
	int quit = 0;
	int can_use_mouse = 1;
	int x = 0;
	int y = 0;
	double scale = 1.0;
	int person_w = 0;
	int person_h = 0;
	int current_screen = 1;
	int color[100];
	for(int i = 0; i < 100; i++) {
		color[i] = 0;
	}
	SDL_Event e;
	if(init_sdl("KiGo Weltdorf") != 0) {
		return -1;
	}
	init_person();
	while(!quit) {
		if((double)screen_width / (double)5000 < (double)screen_height / (double)7500) {
			scale = (double)screen_width / (double)5000;
		} else {
			scale = (double)screen_height / (double)7500;
		}
		person_w = (double)200 * (double)scale;
		person_h = (double)300 * (double)scale;
		double scale2;
		int arrow_w;
		int arrow_h;
		if((double)screen_width / (double)5000 < (double)screen_height / (double)7500) {
			scale2 = (double)screen_width / (double)5000;
		} else {
			scale2 = (double)screen_height / (double)7500;
		}
		arrow_w = (double)200 * (double)scale2;
		arrow_h = (double)100 * (double)scale2;
		while(SDL_PollEvent(&e)) {
			if(SDL_MOUSEBUTTONUP) {
				can_use_mouse = 1;
			}
			if(e.type == SDL_QUIT) {
				quit = 1;
			} else {
				SDL_GetMouseState(&x, &y);
				// mouse input
				std::cout << "1" << std::endl;
				if(current_screen == 1) {
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width * 15 / 16 && x < screen_width * 15 / 16 + arrow_w && y > screen_height * 19 / 20 && y < screen_height * 19 / 20 + arrow_h) {
						current_screen = 2;
						can_use_mouse = 0;
					}
				}
				if(current_screen == 2) {
					// Hunger
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width / 8 - screen_width / 16 && x < screen_width / 8 - screen_width / 16 + screen_width / 8 && y > screen_height * 3 / 5 - screen_height / 24 && y < screen_height * 3 / 5 - screen_height / 24 + screen_height / 12) {
						for(int i = 0; i < 50; i++) {
							color[i] = 2;
						}
						for(int i = 50; i < 70; i++) {
							color[i] = 1;
						}
						for(int i = 70; i < 100; i++) {
							color[i] = 0;
						}
						can_use_mouse = 0;
					}
					// Armut
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 && x < screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 && y > screen_height * 3 / 5 - screen_height / 24 && y < screen_height * 3 / 5 - screen_height / 24 + screen_height / 12) {
						for(int i = 0; i < 46; i++) {
							color[i] = 2;
						}
						for(int i = 46; i < 100; i++) {
							color[i] = 0;
						}
						can_use_mouse = 0;
					}
					// Krieg
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 && x < screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 && y > screen_height * 3 / 5 - screen_height / 24 && y < screen_height * 3 / 5 - screen_height / 24 + screen_height / 12) {
						for(int i = 0; i < 5; i++) {
							color[i] = 2;
						}
						for(int i = 5; i < 100; i++) {
							color[i] = 0;
						}
						can_use_mouse = 0;
					}
					// Wasser
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 && x < screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 && y > screen_height * 3 / 5 - screen_height / 24 && y < screen_height * 3 / 5 - screen_height / 24 + screen_height / 12) {
						for(int i = 0; i < 18; i++) {
							color[i] = 2;
						}
						for(int i = 18; i < 56; i++) {
							color[i] = 1;
						}
						for(int i = 56; i < 100; i++) {
							color[i] = 0;
						}
						can_use_mouse = 0;
					}
					// Obdachlos
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 && x < screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 && y > screen_height * 3 / 5 - screen_height / 24 && y < screen_height * 3 / 5 - screen_height / 24 + screen_height / 12) {
						for(int i = 0; i < 1; i++) {
							color[i] = 2;
						}for(int i = 1; i < 100; i++) {
							color[i] = 0;
						}
						can_use_mouse = 0;
					}
					// Kinder
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width / 8 - screen_width / 16 && x < screen_width / 8 - screen_width / 16 + screen_width / 8 && y > screen_height * 3 / 5 - screen_height / 24 + screen_height / 12 + screen_height / 24 && y < screen_height * 3 / 5 - screen_height / 24 + screen_height / 12 + screen_height / 24 + screen_height / 12) {
						for(int i = 0; i < 27; i++) {
							color[i] = 0;
						}
						for(int i = 27; i < 100; i++) {
							color[i] = 3;
						}
						can_use_mouse = 0;
					}
					// Urlaub
					if(can_use_mouse == 1 && e.type == SDL_MOUSEBUTTONDOWN && x > screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 && x < screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 && y > screen_height * 3 / 5 - screen_height / 24 + screen_height / 12 + screen_height / 24 && y < screen_height * 3 / 5 - screen_height / 24 + screen_height / 12 + screen_height / 24 + screen_height / 12) {
						for(int i = 0; i < 15; i++) {
							color[i] = 0;
						}
						for(int i = 15; i < 100; i++) {
							color[i] = 3;
						}
						can_use_mouse = 0;
					}
				}
			}
		}
		clear_render();
		if(current_screen == 1) {
			// render screen
			render_screen();
			// Asien
			render_person(screen_width * 26 / 50, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 1, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 2, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 3, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 4, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 5, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 6, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 7, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 8, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 9, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 10, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 11, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50 + person_w * 12, screen_height * 6 / 25);
			render_person(screen_width * 26 / 50, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 1, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 2, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 3, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 4, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 5, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 6, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 7, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 8, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 9, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 10, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 11, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50 + person_w * 12, screen_height * 6 / 25 + person_h * 1);
			render_person(screen_width * 26 / 50, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 1, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 2, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 3, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 4, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 5, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 6, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 7, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 8, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 9, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 10, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 11, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50 + person_w * 12, screen_height * 6 / 25 + person_h * 2);
			render_person(screen_width * 26 / 50, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 1, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 2, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 3, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 4, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 5, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 6, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 7, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 8, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 9, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 10, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 11, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50 + person_w * 12, screen_height * 6 / 25 + person_h * 3);
			render_person(screen_width * 26 / 50, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 1, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 2, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 3, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 4, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 5, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 6, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 7, screen_height * 6 / 25 + person_h * 4);
			render_person(screen_width * 26 / 50 + person_w * 8, screen_height * 6 / 25 + person_h * 4);
			// Afrika
			render_person(screen_width * 13 / 32, screen_height * 9 / 20);
			render_person(screen_width * 13 / 32 + person_w * 1, screen_height * 9 / 20);
			render_person(screen_width * 13 / 32 + person_w * 2, screen_height * 9 / 20);
			render_person(screen_width * 13 / 32 + person_w * 3, screen_height * 9 / 20);
			render_person(screen_width * 13 / 32, screen_height * 9 / 20 + person_h * 1);
			render_person(screen_width * 13 / 32 + person_w * 1, screen_height * 9 / 20 + person_h * 1);
			render_person(screen_width * 13 / 32 + person_w * 2, screen_height * 9 / 20 + person_h * 1);
			render_person(screen_width * 13 / 32 + person_w * 3, screen_height * 9 / 20 + person_h * 1);
			render_person(screen_width * 13 / 32, screen_height * 9 / 20 + person_h * 2);
			render_person(screen_width * 13 / 32 + person_w * 1, screen_height * 9 / 20 + person_h * 2);
			render_person(screen_width * 13 / 32 + person_w * 2, screen_height * 9 / 20 + person_h * 2);
			render_person(screen_width * 13 / 32 + person_w * 3, screen_height * 9 / 20 + person_h * 2);
			render_person(screen_width * 13 / 32, screen_height * 9 / 20 + person_h * 3);
			// Europa
			render_person(screen_width * 4 / 11, screen_height * 3 / 12);
			render_person(screen_width * 4 / 11 + person_w * 1, screen_height * 3 / 12);
			render_person(screen_width * 4 / 11 + person_w * 2, screen_height * 3 / 12);
			render_person(screen_width * 4 / 11 + person_w * 3, screen_height * 3 / 12);
			render_person(screen_width * 4 / 11, screen_height * 3 / 12 + person_h * 1);
			render_person(screen_width * 4 / 11 + person_w * 1, screen_height * 3 / 12 + person_h * 1);
			render_person(screen_width * 4 / 11 + person_w * 2, screen_height * 3 / 12 + person_h * 1);
			render_person(screen_width * 4 / 11 + person_w * 3, screen_height * 3 / 12 + person_h * 1);
			render_person(screen_width * 4 / 11, screen_height * 3 / 12 + person_h * 2);
			render_person(screen_width * 4 / 11 + person_w * 1, screen_height * 3 / 12 + person_h * 2);
			render_person(screen_width * 4 / 11 + person_w * 2, screen_height * 3 / 12 + person_h * 2);
			render_person(screen_width * 4 / 11 + person_w * 3, screen_height * 3 / 12 + person_h * 2);
			// Südamerika, Zentralamerika und Karibik
			render_person(screen_width * 1 / 5, screen_height * 6 / 11);
			render_person(screen_width * 1 / 5 + person_w * 1, screen_height * 6 / 11);
			render_person(screen_width * 1 / 5 + person_w * 2, screen_height * 6 / 11);
			render_person(screen_width * 1 / 5 + person_w * 3, screen_height * 6 / 11);
			render_person(screen_width * 1 / 5, screen_height * 6 / 11 + person_h * 1);
			render_person(screen_width * 1 / 5 + person_w * 1, screen_height * 6 / 11 + person_h * 1);
			render_person(screen_width * 1 / 5 + person_w * 2, screen_height * 6 / 11 + person_h * 1);
			render_person(screen_width * 1 / 5 + person_w * 3, screen_height * 6 / 11 + person_h * 1);
			// Kanada und USA
			render_person(screen_width * 1 / 8, screen_height * 1 / 4);
			render_person(screen_width * 1 / 8 + person_w * 1, screen_height * 1 / 4);
			render_person(screen_width * 1 / 8 + person_w * 2, screen_height * 1 / 4);
			render_person(screen_width * 1 / 8, screen_height * 1 / 4 + person_h * 1);
			render_person(screen_width * 1 / 8 + person_w * 1, screen_height * 1 / 4 + person_h * 1);
			// Ozeanien
			render_person(screen_width * 23 / 32, screen_height * 5 / 8);
			// next page
			render_arrow(screen_width * 15 / 16, screen_height * 19 / 20);
		}
		if(current_screen == 2) {
			render_statistics(color);
			render_buttons();
		}
		render();
	}
	quit_person();
	close_sdl();
	return 0;
}
