#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include <memory>
#include <SDL.h>

class Window {
public:
	static void Init(std::string = "Window");

	static void Quit();

	static void RenderTexture(SDL_Texture *, ...);

	static SDL_Texture* LoadTexture(std::string);

	static SDL_Texture* RenderText(std::string, std::string, SDL_Color, int);

	static void Clear();

	static void Present();

	static SDL_Rect Box();
	
private:
	static std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> _window;
	static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> _renderer;
	static SDL_Rect _box;
};

#endif