#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include <SDL.h>

class Window {
public:
	static void Init();

	static void Quit();

	static void RenderTexture(SDL_Texture *, ...);

	static SDL_Texture* LoadTexture(std::string);

	static SDL_Texture* RenderText(std::string, std::string, SDL_Color, int);

	static void Clear();

	static void Present();

	static SDL_Rect Box();
	
private:
	static SDL_Window* _window;
	static SDL_Renderer* _renderer;
	static SDL_Rect _box;
};

#endif