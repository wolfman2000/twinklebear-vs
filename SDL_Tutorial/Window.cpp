#include "Window.hpp"

// static calls get initialized up at the top.
std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> Window::_window = 
	std::unique_ptr<SDL_Window, void (*)(SDL_Window *)>(nullptr, SDL_DestroyWindow);

std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> Window::_renderer =
	std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)>(nullptr, SDL_DestroyRenderer);

SDL_Rect Window::_box;