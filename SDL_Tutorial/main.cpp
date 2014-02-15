#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_Image.h>

int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;

// focusing on square tiles.
int const TILE_SIZE = 40;

void logSDLError(std::ostream &os, std::string const &msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(std::string const &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) {
		logSDLError(std::cout, "LoadTExture");
	}

	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, nullptr, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr) {
	SDL_Rect dst;
	dst.x = x;
	dst.y =y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}

int main(int argc, char **argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		logSDLError(std::cout, "IMG_Init");
		return 2;
	}

	// TODO: Smart pointers at some points.
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		return 3;
	}

	auto renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, renderFlags);
	if (ren == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		return 4;
	}

	SDL_Texture *image = loadTexture("image.png", ren);
	if (image == nullptr) {
		return 5;
	}
	
	SDL_Event evt;
	bool quit = false;
	int x = 0;
	int y = 0;

	while (!quit) {
		// process all events that took place since the last "time".
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) {
				// user is closing the window.
				quit = true;
			}
			else if (evt.type == SDL_KEYDOWN) {
				// user presses any key.
				switch (evt.key.keysym.sym) {
				case SDLK_DOWN:
					++y;
					break;
				case SDLK_UP:
					--y;
					break;
				case SDLK_LEFT:
					--x;
					break;
				case SDLK_RIGHT:
					++x;
					break;
				default:
					quit = true;
				}
			}
			else if (evt.type == SDL_MOUSEBUTTONDOWN) {
				// User presses a mouse button.
				quit = true;
			}
		}

		SDL_RenderClear(ren);

		renderTexture(image, ren, x, y);

		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	IMG_Quit();
	SDL_Quit();

	return 0;
}