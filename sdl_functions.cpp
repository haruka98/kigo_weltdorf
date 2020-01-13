#include "sdl_functions.hpp"

int screen_width = 1920;
int screen_height = 1080;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

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
