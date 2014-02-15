#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include <memory>
#include <SDL.h>

class Window {
public:
	static void Init(std::string = "Window");

	static void Quit();

	static void RenderTexture(SDL_Texture *, SDL_Rect &, SDL_Rect * = nullptr, float = 0.0, int = 0, int = 0, SDL_RendererFlip = SDL_FLIP_NONE);

	static SDL_Texture* LoadTexture(std::string const &);

	static SDL_Texture* RenderText(std::string const &, std::string const &, SDL_Color, int);

	static void Clear();

	static void Present();

	static SDL_Rect Box();
	
private:
	static std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> _window;
	static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> _renderer;
	static SDL_Rect _box;
};

#endif