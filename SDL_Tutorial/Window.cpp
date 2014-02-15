#include "Window.hpp"
#include <SDL_ttf.h>

// static calls get initialized up at the top.
std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> Window::_window = 
	std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>(nullptr, SDL_DestroyWindow);

std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> Window::_renderer =
	std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>(nullptr, SDL_DestroyRenderer);

SDL_Rect Window::_box;

void Window::Init(std::string title) {
	// set up all subsystems.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		throw std::runtime_error("SDL Init Failed");
	}
	if (TTF_Init() == -1) {
		throw std::runtime_error("TTF Init Failed");
	}

	_box.x = 0;
	_box.y = 0;
	_box.w = 640;
	_box.h = 480;

	_window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _box.w, _box.h, SDL_WINDOW_SHOWN));
	if (_window == nullptr) {
		throw std::runtime_error("Failed to create window");
	}

	_renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (_renderer == nullptr) {
		throw std::runtime_error("Faled to create renderer");
	}
}

void Window::Quit() {
	TTF_Quit();
	SDL_Quit();
}

void Window::RenderTexture(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip) {
	// convert coordinates appropriately.
	xPivot += dstRect.w / 2;
	yPivot += dstRect.h / 2;
	SDL_Point pivot = { xPivot, yPivot };

	SDL_RenderCopyEx(_renderer.get(), tex,clip, &dstRect, angle, &pivot, flip);
}