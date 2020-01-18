#include "sdl_functions.hpp"

int screen_width = 1920;
int screen_height = 1080;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

SDL_Surface* person = NULL;
SDL_Texture* person_texture = NULL;
SDL_Surface* person_1 = NULL;
SDL_Texture* person_texture_1 = NULL;
SDL_Surface* person_2 = NULL;
SDL_Texture* person_texture_2 = NULL;
SDL_Surface* person_3 = NULL;
SDL_Texture* person_texture_3 = NULL;

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

int init_sdl(char* window_name) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 1;
	} else {
		TTF_Init();
		gWindow = SDL_CreateWindow(window_name, 0, 10, screen_width, screen_height, SDL_WINDOW_RESIZABLE);
		SDL_Surface* icon = IMG_Load("l_data/ico.bmp");
		SDL_SetWindowIcon(gWindow, icon);
		SDL_FreeSurface(icon);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return 2;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return 4;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return 5;
				}
			}
		}
	}
	return 0;
}

int close_sdl() {
	for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void render() {
	SDL_RenderPresent(gRenderer);
}

void clear_render() {
	SDL_GetWindowSize(gWindow, &screen_width, &screen_height);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

SDL_Color nCol(int r, int g, int b) {
	SDL_Color col={r,g,b};
	return col;
}

void render_text(char* text, int x, int y, int size, int center, int f_color) {
	TTF_Font* font = TTF_OpenFont("arial.ttf", size);
	SDL_Color color = {255, 255, 255};
	if(f_color == 1) {
		color = nCol(0, 0, 0);
	}
	if(f_color == 2) {
		color = nCol(0xFF, 0xFF, 0x00);
	}
	if(f_color == 3) {
		color = nCol(0x11, 0x11, 0xFF);
	}
	SDL_Surface* surfaceMessage = TTF_RenderUTF8_Blended(font, text, color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
	int w = 0;
	int h = 0;
	SDL_QueryTexture(Message, NULL, NULL, &w, &h);
	SDL_Rect Message_rect;
	if(center == 1) {
		x = x - (w / 2);
		y = y - (h / 2);
	}
	if(center == 2) {
		x = x - w;
	}
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = w;
	Message_rect.h = h;
	SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(font);
}

void render_screen() {
	SDL_Surface* back_1 = NULL;
	SDL_Texture* back_texture = NULL;
	SDL_Rect base_back_1;
	base_back_1.x = 0;
	base_back_1.y = 0;
	base_back_1.w = 1357;
	base_back_1.h = 628;
	double scale = (double)screen_width * (5.0 / 6.0) / (double)base_back_1.w;
	if(scale * (double)base_back_1.h > (double)screen_height) {
		scale = (double)screen_height / (double)base_back_1.h;
	}
	SDL_Rect position_back_1;
	position_back_1.w = (double)base_back_1.w * scale + 2;
	position_back_1.h = (double)base_back_1.h * scale;
	position_back_1.x = (screen_width * 11) / 12 / 2 - position_back_1.w / 2 - 1;
	position_back_1.y = screen_height / 2 - position_back_1.h / 2;
	back_1 = IMG_Load("weltkarte.png");
	back_texture = SDL_CreateTextureFromSurface(gRenderer, back_1);
	SDL_RenderCopy(gRenderer, back_texture, &base_back_1, &position_back_1);
	SDL_FreeSurface(back_1);
	SDL_DestroyTexture(back_texture);
}

void render_person(int x, int y) {
	double scale = 1.0;
	SDL_Rect person_base;
	person_base.x = 0;
	person_base.y = 0;
	person_base.w = 400;
	person_base.h = 600;
	SDL_Rect person_position;
	person_position.x = x;
	person_position.y = y;
	if((double)screen_width / (double)5000 < (double)screen_height / (double)7500) {
		scale = (double)screen_width / (double)5000;
	} else {
		scale = (double)screen_height / (double)7500;
	}
	person_position.w = (double)200 * (double)scale;
	person_position.h = (double)300 * (double)scale;
	SDL_RenderCopy(gRenderer, person_texture, &person_base, &person_position);
}


void render_big_person(int x, int y, int color) {
	double scale = 1.0;
	SDL_Rect person_base;
	person_base.x = 0;
	person_base.y = 0;
	person_base.w = 400;
	person_base.h = 600;
	SDL_Rect person_position;
	person_position.x = x;
	person_position.y = y;
	if((double)screen_width / (double)2500 < (double)screen_height / (double)3750) {
		scale = (double)screen_width / (double)2500;
	} else {
		scale = (double)screen_height / (double)3750;
	}
	person_position.w = (double)200 * (double)scale;
	person_position.h = (double)300 * (double)scale;
	switch(color) {
		case 0: {
			SDL_RenderCopy(gRenderer, person_texture, &person_base, &person_position);
			break;
		}
		case 1: {
			SDL_RenderCopy(gRenderer, person_texture_1, &person_base, &person_position);
			break;
		}
		case 2: {
			SDL_RenderCopy(gRenderer, person_texture_2, &person_base, &person_position);
			break;
		}
		case 3: {
			SDL_RenderCopy(gRenderer, person_texture_3, &person_base, &person_position);
			break;
		}
	}
}

void init_person() {
	person = IMG_Load("gummibaerchen.png");
	person_texture = SDL_CreateTextureFromSurface(gRenderer, person);
	person_1 = IMG_Load("gummibaerchen_1.png");
	person_texture_1 = SDL_CreateTextureFromSurface(gRenderer, person_1);
	person_2 = IMG_Load("gummibaerchen_2.png");
	person_texture_2 = SDL_CreateTextureFromSurface(gRenderer, person_2);
	person_3 = IMG_Load("gummibaerchen_3.png");
	person_texture_3 = SDL_CreateTextureFromSurface(gRenderer, person_3);
}

void quit_person() {
	SDL_FreeSurface(person);
	SDL_DestroyTexture(person_texture);
	SDL_FreeSurface(person_1);
	SDL_DestroyTexture(person_texture_1);
	SDL_FreeSurface(person_2);
	SDL_DestroyTexture(person_texture_2);
	SDL_FreeSurface(person_3);
	SDL_DestroyTexture(person_texture_3);
}

void render_statistics(int color[100]) {
	int i = 0;
	double scale = 1.0;
	if((double)screen_width / (double)2500 < (double)screen_height / (double)3750) {
		scale = (double)screen_width / (double)2500;
	} else {
		scale = (double)screen_height / (double)3750;
	}
	int person_w = (double)200 * (double)scale;
	int person_h = (double)300 * (double)scale;
	// first row
	render_big_person(screen_width * 1 / 2 - person_w * 19 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 17 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 15 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 13 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 11 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 9 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 7 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 5 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 3 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 1 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 1 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 3 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 5 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 7 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 9 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 11 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 13 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 15 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 17 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 19 / 2, screen_height * 1 / 2 - person_h * 9 / 2, color[i]);
	i++;
	// second row
	render_big_person(screen_width * 1 / 2 - person_w * 19 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 17 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 15 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 13 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 11 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 9 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 7 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 5 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 3 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 1 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 1 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 3 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 5 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 7 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 9 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 11 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 13 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 15 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 17 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 19 / 2, screen_height * 1 / 2 - person_h * 7 / 2, color[i]);
	i++;
	// third row
	render_big_person(screen_width * 1 / 2 - person_w * 19 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 17 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 15 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 13 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 11 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 9 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 7 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 5 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 3 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 1 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 1 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 3 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 5 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 7 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 9 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 11 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 13 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 15 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 17 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 19 / 2, screen_height * 1 / 2 - person_h * 5 / 2, color[i]);
	i++;
	// fourth row
	render_big_person(screen_width * 1 / 2 - person_w * 19 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 17 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 15 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 13 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 11 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 9 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 7 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 5 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 3 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 1 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 1 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 3 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 5 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 7 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 9 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 11 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 13 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 15 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 17 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 19 / 2, screen_height * 1 / 2 - person_h * 3 / 2, color[i]);
	i++;
	// fifth row
	render_big_person(screen_width * 1 / 2 - person_w * 19 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 17 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 15 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 13 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 11 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 9 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 7 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 5 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 3 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 - person_w * 1 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 1 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 3 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 5 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 7 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 9 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 11 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 13 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 15 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 17 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	render_big_person(screen_width * 1 / 2 + person_w * 19 / 2, screen_height * 1 / 2 - person_h * 1 / 2, color[i]);
	i++;
	
}

void render_buttons() {
	// Hunger
	SDL_Rect rect;
	rect.w = screen_width / 8;
	rect.h = screen_height / 12;
	rect.x = screen_width / 8 - screen_width / 16;
	rect.y = screen_height * 3 / 5 - screen_height / 24;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rect);
	int xval, yval;
	SDL_GetMouseState(&xval, &yval);
	if(xval > rect.x &&
		xval < rect.x + rect.w &&
		yval > rect.y &&
		yval < rect.y + rect.h) {
		SDL_Rect mrect;
		mrect.w = rect.w + 2;
		mrect.h = rect.h + 2;
		mrect.x = rect.x - 1;
		mrect.y = rect.y - 1;
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &mrect);
	}
	render_text("Hunger", screen_width / 8, screen_height * 3 / 5, 30, 1, 1);
	// Armut
	rect.w = screen_width / 8;
	rect.h = screen_height / 12;
	rect.x = screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16;
	rect.y = screen_height * 3 / 5 - screen_height / 24;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_GetMouseState(&xval, &yval);
	if(xval > rect.x &&
		xval < rect.x + rect.w &&
		yval > rect.y &&
		yval < rect.y + rect.h) {
		SDL_Rect mrect;
		mrect.w = rect.w + 2;
		mrect.h = rect.h + 2;
		mrect.x = rect.x - 1;
		mrect.y = rect.y - 1;
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &mrect);
	}
	render_text("Armut", screen_width / 8 + screen_width / 8 + screen_width / 16, screen_height * 3 / 5, 30, 1, 1);
	// Krieg
	rect.w = screen_width / 8;
	rect.h = screen_height / 12;
	rect.x = screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16;
	rect.y = screen_height * 3 / 5 - screen_height / 24;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_GetMouseState(&xval, &yval);
	if(xval > rect.x &&
		xval < rect.x + rect.w &&
		yval > rect.y &&
		yval < rect.y + rect.h) {
		SDL_Rect mrect;
		mrect.w = rect.w + 2;
		mrect.h = rect.h + 2;
		mrect.x = rect.x - 1;
		mrect.y = rect.y - 1;
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &mrect);
	}
	render_text("Krieg", screen_width / 8 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16, screen_height * 3 / 5, 30, 1, 1);
	// Wasser
	rect.w = screen_width / 8;
	rect.h = screen_height / 12;
	rect.x = screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16;
	rect.y = screen_height * 3 / 5 - screen_height / 24;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_GetMouseState(&xval, &yval);
	if(xval > rect.x &&
		xval < rect.x + rect.w &&
		yval > rect.y &&
		yval < rect.y + rect.h) {
		SDL_Rect mrect;
		mrect.w = rect.w + 2;
		mrect.h = rect.h + 2;
		mrect.x = rect.x - 1;
		mrect.y = rect.y - 1;
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &mrect);
	}
	render_text("Wasser", screen_width / 8 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16, screen_height * 3 / 5, 30, 1, 1);
	// Obdachlos
	rect.w = screen_width / 8;
	rect.h = screen_height / 12;
	rect.x = screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16;
	rect.y = screen_height * 3 / 5 - screen_height / 24;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_GetMouseState(&xval, &yval);
	if(xval > rect.x &&
		xval < rect.x + rect.w &&
		yval > rect.y &&
		yval < rect.y + rect.h) {
		SDL_Rect mrect;
		mrect.w = rect.w + 2;
		mrect.h = rect.h + 2;
		mrect.x = rect.x - 1;
		mrect.y = rect.y - 1;
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &mrect);
	}
	render_text("Obdachlos", screen_width / 8 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16 + screen_width / 8 + screen_width / 16, screen_height * 3 / 5, 30, 1, 1);
	// Kinder
	rect.w = screen_width / 8;
	rect.h = screen_height / 12;
	rect.x = screen_width / 8 - screen_width / 16;
	rect.y = screen_height * 3 / 5 - screen_height / 24 + screen_height / 12 + screen_height / 24;
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_GetMouseState(&xval, &yval);
	if(xval > rect.x &&
		xval < rect.x + rect.w &&
		yval > rect.y &&
		yval < rect.y + rect.h) {
		SDL_Rect mrect;
		mrect.w = rect.w + 2;
		mrect.h = rect.h + 2;
		mrect.x = rect.x - 1;
		mrect.y = rect.y - 1;
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &mrect);
	}
	render_text("Kinder", screen_width / 8, screen_height * 3 / 5 + screen_height / 12 + screen_height / 24, 30, 1, 1);
	// Urlaub
	rect.w = screen_width / 8;
	rect.h = screen_height / 12;
	rect.x = screen_width / 8 - screen_width / 16 + screen_width / 8 + screen_width / 16;
	rect.y = screen_height * 3 / 5 - screen_height / 24 + screen_height / 12 + screen_height / 24;
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_GetMouseState(&xval, &yval);
	if(xval > rect.x &&
		xval < rect.x + rect.w &&
		yval > rect.y &&
		yval < rect.y + rect.h) {
		SDL_Rect mrect;
		mrect.w = rect.w + 2;
		mrect.h = rect.h + 2;
		mrect.x = rect.x - 1;
		mrect.y = rect.y - 1;
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &mrect);
	}
	render_text("Urlaub", screen_width / 8 + screen_width / 8 + screen_width / 16, screen_height * 3 / 5 + screen_height / 12 + screen_height / 24, 30, 1, 1);
}

void render_arrow(int x, int y) {
	double scale = 1.0;
	SDL_Surface* arrow = IMG_Load("arrow.png");
	SDL_Texture* arrow_texture = SDL_CreateTextureFromSurface(gRenderer, arrow);
	SDL_Rect arrow_base;
	arrow_base.x = 0;
	arrow_base.y = 0;
	arrow_base.w = 200;
	arrow_base.h = 100;
	SDL_Rect arrow_position;
	arrow_position.x = x;
	arrow_position.y = y;
	if((double)screen_width / (double)5000 < (double)screen_height / (double)7500) {
		scale = (double)screen_width / (double)5000;
	} else {
		scale = (double)screen_height / (double)7500;
	}
	arrow_position.w = (double)200 * (double)scale;
	arrow_position.h = (double)100 * (double)scale;
	SDL_RenderCopy(gRenderer, arrow_texture, &arrow_base, &arrow_position);
	SDL_FreeSurface(arrow);
	SDL_DestroyTexture(arrow_texture);
}
