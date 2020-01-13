main:
	g++ -o weltdorf main.cpp sdl_functions.cpp -I.\mingw_dev_lib\include\SDL2 -L.\mingw_dev_lib\lib -std=c++11 -w -Wl,-subsystem,windows -lws2_32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
