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

	// TODO: Smart pointers at some points.
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		return 2;
	}

	auto renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, renderFlags);
	if (ren == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		return 3;
	}

	SDL_Texture *image = loadTexture("image.bmp", ren);
	SDL_Texture *background = loadTexture("background.bmp", ren);
	if (image == nullptr || background == nullptr) {
		return 4;
	}

	SDL_RenderClear(ren);
	
	int bgWidth, bgHeight;
	SDL_QueryTexture(background, nullptr, nullptr, &bgWidth, &bgHeight);
	for (int gridX = 0; gridX < SCREEN_WIDTH / bgWidth; ++gridX) {
		for (int gridY = 0; gridY < SCREEN_HEIGHT / bgHeight; ++gridY) {
			renderTexture(background, ren, gridX * bgWidth, gridY * bgHeight);
		}
	}
	
	int igWidth, igHeight;
	SDL_QueryTexture(image, nullptr, nullptr, &igWidth, &igHeight);
	renderTexture(image, ren, SCREEN_WIDTH / 2 - igWidth / 2, SCREEN_HEIGHT / 2 - igHeight / 2);

	SDL_RenderPresent(ren);

	SDL_Delay(2000);

	SDL_DestroyTexture(image);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}