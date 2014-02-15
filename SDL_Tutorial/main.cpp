#include <iostream>
#include "Window.hpp"

int main(int argc, char **argv) {
	try {
		Window::Init("Hello World!");
	}
	catch (std::runtime_error const &e) {
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}

	SDL_Texture *img, *msg;
	try {
		std::string imgFile = "image.png";
		img = Window::LoadTexture(imgFile);

		std::string fontFile = "SourceSansPro-Regular.ttf";
		std::string text = "TTF Fonts too!";
		SDL_Color color = { 255, 255, 255 };
		msg = Window::RenderText(text, fontFile, color, 25);
	}
	catch (std::runtime_error const &e) {
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}

	auto box = Window::Box();
	SDL_Rect pos = { box.w / 2 - 150 / 2, box.h / 2 - 150 / 2, 150, 150 };
	float angle = 0;
	
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
				switch (evt.key.keysym.sym) {
				case SDLK_d:
					angle += 2;
					break;
				case SDLK_a:
					angle -= 2;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
			}
		}

		Window::Clear();

		Window::RenderTexture(img, pos, nullptr, angle);
		Window::RenderTexture(img, pos, nullptr, angle, 0, 0, SDL_FLIP_VERTICAL);

		Window::Present();
	}

	SDL_DestroyTexture(img);
	SDL_DestroyTexture(msg);

	Window::Quit();
	return 0;
}