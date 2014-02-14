#include <iostream>
#include <string>
#include <SDL.h>

int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, std::string const &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	// TODO: Smart pointers at some points.
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		logSDLError(std::cout, "SDL_CreateWindow");
		return 1;
	}

	auto renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, renderFlags);
	if (ren == nullptr) {
		logSDLError(std::cout, "SDL_CreateRenderer");
		return 1;
	}

	SDL_Surface *bmp = SDL_LoadBMP("hello.bmp");
	if (bmp == nullptr) {
		logSDLError(std::cout, "SDL_LoadBMP");
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	// At this point, we no longer need the bmp surface.
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		logSDLError(std::cout, "SDL_CreateTextureFromSurface");
		return 1;
	}

	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, nullptr, nullptr);
	SDL_RenderPresent(ren);

	SDL_Delay(2000);

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}