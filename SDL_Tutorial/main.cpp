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

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, nullptr, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	int w, h;
	// by querying the texture, we can utilize its width and height.
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
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

	while (!quit) {
		// process all events that took place since the last "time".
		while (SDL_PollEvent(&evt)) {
			if (evt.type == SDL_QUIT) {
				// user is closing the window.
				quit = true;
			}
			else if (evt.type == SDL_KEYDOWN) {
				// user presses any key.
				quit = true;
			}
			else if (evt.type == SDL_MOUSEBUTTONDOWN) {
				// User presses a mouse button.
				quit = true;
			}
		}

		SDL_RenderClear(ren);

		int igWidth, igHeight;
		SDL_QueryTexture(image, nullptr, nullptr, &igWidth, &igHeight);
		renderTexture(image, ren, SCREEN_WIDTH / 2 - igWidth / 2, SCREEN_HEIGHT / 2 - igHeight / 2);

		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	IMG_Quit();
	SDL_Quit();

	return 0;
}