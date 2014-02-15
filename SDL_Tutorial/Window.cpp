#include "Window.hpp"
#include <SDL_ttf.h>
#include <SDL_image.h>

// static calls get initialized up at the top.
std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> Window::_window = 
	std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>(nullptr, SDL_DestroyWindow);

std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> Window::_renderer =
	std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>(nullptr, SDL_DestroyRenderer);

SDL_Rect Window::_box;

void Window::Init(std::string title, int width, int height) {
	// set up all subsystems.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		throw std::runtime_error("SDL Init Failed");
	}
	if (TTF_Init() == -1) {
		throw std::runtime_error("TTF Init Failed");
	}

	_box.x = 0;
	_box.y = 0;
	_box.w = width;
	_box.h = height;

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

SDL_Texture* Window::LoadTexture(std::string const &file) {
	SDL_Texture *texture = IMG_LoadTexture(_renderer.get(), file.c_str());
	if (texture == nullptr) {
		throw std::runtime_error("Failed to create texture");
	}

	return texture;
}

SDL_Texture* Window::RenderText(std::string const &message, std::string const &fontFile, SDL_Color color, int fontSize) {
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr) {
		throw std::runtime_error("Failed to create font");
		return nullptr;
	}

	// fonts must be rendered onto a surface to be effective.
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr) {
		TTF_CloseFont(font);
		throw std::runtime_error("Failed to create surface");
		return nullptr;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer.get(), surf);
	if (texture == nullptr) {
		throw std::runtime_error("Failed to create texture");
	}

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

void Window::Clear() {
	SDL_RenderClear(_renderer.get());
}

void Window::Present() {
	SDL_RenderPresent(_renderer.get());
}

SDL_Rect Window::Box() {
	// update the box variable.
	SDL_GetWindowSize(_window.get(), &_box.w, &_box.h);
	return _box;
}